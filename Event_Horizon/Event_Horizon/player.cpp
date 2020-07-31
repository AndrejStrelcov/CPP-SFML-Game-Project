#include "player.h"

//Private functions
void Player::initVariables()
{
	//Player abilities
	movementSpeed = 10.f;
	attackCooldownMax = 10.f;
	attackCooldown = attackCooldownMax;

	hpMax = 100;
	hp = hpMax;
}

void Player::initTexture()
{
	//Load player texture from Textures folder
	if (!texture.loadFromFile("Textures/spaceship.png"))
	{
		cout << "ERROR::PLAYER.H::INITTEXTURE::Could not load texture file!" << "\n";
	}
}

void Player::initSprite()
{
	//Set texture to sprite
	sprite.setTexture(texture);

	//Resize texture
	sprite.scale(0.2f, 0.2f);
}

//Constructors
Player::Player()
{
	initVariables();
	initTexture();
	initSprite();
}

//Destructors
Player::~Player()
{
	
}

//Accessors
const Vector2f& Player::getPos() const
{
	return sprite.getPosition();
}

const FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return hp;
}

const int& Player::getHpMax() const
{
	return hpMax;
}

//Modifiers
void Player::setPosition(const Vector2f pos)
{
	sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
	if (hp < 0)
		this->hp = 0;
}

void Player::loseHp(const int value)
{
	hp -= value;
}

//Public functions
void Player::move(const float dirX, const float dirY)
{
	//Sprite movement
	sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}

const bool Player::ableToAttack()
{
	if (attackCooldown >= attackCooldownMax)
	{
		attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (attackCooldown < attackCooldownMax)
		attackCooldown += 0.5f;
}

void Player::update()
{
	updateAttack();
}

void Player::render(RenderTarget& target)
{
	//Draws sprite
	target.draw(sprite);
}
