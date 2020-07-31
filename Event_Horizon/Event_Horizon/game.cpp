#include "game.h"

//Private functions
void Game::initWindow()
{
	window = new RenderWindow(VideoMode(1280, 960), "Event Horizon", Style::Close | Style::Titlebar);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
}

void Game::initMenu()
{

}

void Game::initTextures()
{
	textures["BULLET"] = new Texture();
	textures["BULLET"]->loadFromFile("Textures/laser.png");
}

void Game::initGUI()
{
	//Load font
	if (!font.loadFromFile("Fonts/Minecraftia.ttf"))
		cout << "ERROR::GAME::Failed to load font!" << "\n";

	//Initialize text
	GUItext.setFont(font);
	GUItext.setCharacterSize(24);
	GUItext.setFillColor(Color::White);
	GUItext.setPosition(Vector2f(20.f, 50.f));

	//Initialize game over text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(Vector2f(320.f, 400.f));
	gameOverText.setString("GAME OVER!");

	underGameOverText.setFont(font);
	underGameOverText.setCharacterSize(20);
	underGameOverText.setFillColor(Color::White);
	underGameOverText.setPosition(Vector2f(530.f, 520.f));
	underGameOverText.setString("Press esc to exit");

	//Initialize game over background
	if (!gameOverWorldBackgroundTexture.loadFromFile("Textures/background.jpg"))
	{
		cout << "ERROR:GAME::Could not load game over background texture!" << "\n";
	}

	gameOverWorldBackground.setTexture(gameOverWorldBackgroundTexture);

	gameOverWorldBackground.scale(2.f, 2.f);

	//Initialize player GUI
	playerHpBar.setSize(Vector2f(300.f, 25.f));
	playerHpBar.setFillColor(Color(0, 128, 0, 225));
	playerHpBar.setPosition(Vector2f(20.f, 20.f));

	playerHpBarBack = playerHpBar;
	playerHpBarBack.setFillColor(Color(120, 120, 120, 200));
}

void Game::initBackground()
{
	if (!worldBackgroundTexture.loadFromFile("Textures/background.jpg"))
	{
		cout << "ERROR:GAME::Could not load background texture!" << "\n";
	}

	worldBackground.setTexture(worldBackgroundTexture);

	worldBackground.scale(2.f, 2.f);
}

void Game::initSystems()
{
	score = 0;
}

void Game::initPlayer()
{
	player = new Player();
}

void Game::initEnemies()
{
	spawnTimerMax = 40.f;
	spawnTimer = spawnTimerMax;

	//Old enemy spawn timer
	/*enemy = new Enemy(20.f, 20.f);*/
}

//Constructors
Game::Game()
{
	initWindow();
	initTextures();
	initGUI();
	initBackground();
	initSystems();
	initPlayer();
	initEnemies();
}

//Destructors
Game::~Game()
{
	delete window;
	delete player;

	//Delete textures
	for (auto &i : textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto *i : bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto *i : enemies)
	{
		delete i;
	}
}

//Public functions
void Game::run()
{
	//Updating and rendering while running
	while (window->isOpen())
	{
		updatePollEvents();

		if(player->getHp() > 0)
			update();

		render();
	}
}

//Updates
void Game::updatePollEvents()
{
	//Close window
	Event ev;
	while (window->pollEvent(ev))
	{
		if (ev.Event::type == Event::Closed)
			window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::Escape)
			window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (Keyboard::isKeyPressed(Keyboard::A))
		player->move(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::D))
		player->move(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::W))
		player->move(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::S))
		player->move(0.f, 1.f);

	//Shooting mechanics
	if (Mouse::isButtonPressed(Mouse::Left) && player->ableToAttack())
	{
		bullets.push_back
		(
			new Bullet(textures["BULLET"], 
			player->getPos().x + player->getBounds().width/2.f, 
			player->getPos().y, 
			0.f, 
			-1.f, 
			15.f)
		);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space) && player->ableToAttack())
	{
		bullets.push_back
		(
			new Bullet(textures["BULLET"],
				player->getPos().x + player->getBounds().width / 2.f,
				player->getPos().y,
				0.f,
				-1.f,
				15.f)
		);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : bullets)
	{
		bullet->update();

		//Cullling bullets to top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Deletes bullets
			delete bullets.at(counter);
			bullets.erase(bullets.begin() + counter);

			//Notifies if bullets are getting deleted
			cout << "Bullets: " << bullets.size() << "\n";
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawn enemies
	spawnTimer += 1.f;
	if (spawnTimer > spawnTimerMax)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x-10.f, -50.f));
		spawnTimer = 0.f;
	}

	//Update enemies
	unsigned counter = 0;
	for (auto *enemy : enemies)
	{
		enemy->update();

		//Cullling enemies to top of screen
		if (enemy->getBounds().top > window->getSize().y)
		{
			//Deletes enemy when intersects with bullet
			player->loseHp(enemies.at(counter)->getDamage());
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);

			//Notifies if enemies are getting deleted
			cout << "Enemies: " << enemies.size() << "\n";
		}
		else if (enemy->getBounds().intersects(player->getBounds()))
		{
			//Deletes enemy when intersects with player and deals damage to player
			player->loseHp(enemies.at(counter)->getDamage());
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateCombat()
{
	//Enemy and bullet collision
	for (int i = 0; i < enemies.size(); i++)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < bullets.size() && enemy_deleted == false; k++)
		{
			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
				score += enemies[i]->getPoints();

				delete enemies[i];
				enemies.erase(enemies.begin() + i);

				delete bullets[k];
				bullets.erase(bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

//Renders
void Game::updateGUI()
{
	//Score
	stringstream ss;

	ss << "Score: " << score;

	GUItext.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(player->getHp()) / player->getHpMax();
	playerHpBar.setSize(Vector2f(300.f * hpPercent, playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Player and window collision
	if (player->getBounds().left < 0.f)
	{
		player->setPosition(0.f, player->getBounds().top);
	}
	else if (player->getBounds().left + player->getBounds().width >= window->getSize().x)
	{
		player->setPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);
	}

	if (player->getBounds().top < 0.f)
	{
		player->setPosition(player->getBounds().left, 0.f);
	}
	else if (player->getBounds().top + player->getBounds().height >= window->getSize().y)
	{
		player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
	}
}

void Game::update()
{
	updateInput();
	player->update();
	updateCollision();
	updateBullets();
	updateEnemies();
	updateCombat();
	updateGUI();
	updateWorld();
}

void Game::renderMenu()
{
}

void Game::renderGUI()
{
	window->draw(GUItext);
	window->draw(playerHpBarBack);
	window->draw(playerHpBar);

}

void Game::renderWorld()
{
	window->draw(worldBackground);
}

void Game::render()
{
	//Clears old window
	window->clear();

	//Starts drawing
	renderWorld();

	player->render(*window);

	for (auto *bullet : bullets)
	{
		bullet->render(window);
	}

	for (auto *enemy : enemies)
	{
		enemy->render(window);
	}

	renderGUI();

	if (player->getHp() <= 0)
	{
		window->draw(gameOverWorldBackground);
		window->draw(gameOverText);
		window->draw(underGameOverText);
	}

	//Finish drawing
	window->display();
}