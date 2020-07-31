#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Enemy
{
private:
	//Asteroids
	unsigned pointCount;
	CircleShape shape;
	Texture asteroid;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	//Public functions
	void initVariables();
	void initShape();
	void initTexture();

public:
	//Constructors & Distructors
	Enemy(float posX, float posY);
	virtual ~Enemy();

	//Accessors
	const FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Public functions
	void update();
	void render(RenderTarget* target);
};

#endif
