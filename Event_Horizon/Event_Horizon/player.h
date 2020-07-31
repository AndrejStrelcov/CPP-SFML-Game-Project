#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player
{
private:
	//Player
	Sprite sprite;
	Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	//Constructors & Destructors
	Player();
	virtual ~Player();

	//Accessors
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Public functions
	void move(const float dirX, const float dirY);
	const bool ableToAttack();

	void updateAttack();
	void update();
	void render(RenderTarget& target);
};

#endif