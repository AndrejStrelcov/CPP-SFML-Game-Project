#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <sstream>
#include "player.h"
#include "bullet.h"
#include "enemy.h"

using namespace std;

class Game 
{
private:
	//Window
	RenderWindow* window;

	//Resources
	map<string, Texture*> textures;
	vector<Bullet*> bullets;

	//GUI
	Font font;
	Text GUItext;

	//Game Over
	Text gameOverText;
	Text underGameOverText;
	Texture gameOverWorldBackgroundTexture;
	Sprite gameOverWorldBackground;

	//World
	Texture worldBackgroundTexture;
	Sprite worldBackground;

	//Systems
	unsigned score;

	//Player
	Player* player;

	//Player GUI
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initMenu();
	void initTextures();
	void initGUI();
	void initBackground();
	void initSystems();

	void initPlayer();
	void initEnemies();

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//Public functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderMenu();
	void renderGUI();
	void renderWorld();
	void render();
};

#endif