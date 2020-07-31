#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

class Bullet
{
private:
	//Laser
	Sprite shape;

	Vector2f direction;
	float movementSpeed;

public:
	//Constructors & Destructors
	Bullet();
	Bullet(Texture* texture, float posX, float posY, float dirX, float dirY, float speed);
	virtual ~Bullet();

	//Accesors
	const FloatRect getBounds() const;

	//Public functions
	void update();
	void render(RenderTarget* target);
};

#endif