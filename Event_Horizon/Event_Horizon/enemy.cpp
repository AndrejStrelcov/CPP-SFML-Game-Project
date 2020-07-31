#include "enemy.h"

//Public functions
void Enemy::initVariables()
{
	pointCount = rand() % 8 + 3;
	type = 0;
	speed = static_cast<float>(pointCount / 1.5);
	hpMax = static_cast<int>(pointCount * 5);
	hp = hpMax;
	damage = pointCount;
	points = pointCount;
}

void Enemy::initShape()
{
	shape.setRadius(pointCount * 10);
	shape.setPointCount(pointCount);
	shape.setFillColor(Color(128, 64, rand() % 50 + 10, 255));
}

void Enemy::initTexture()
{
	//Load enemy texture from Textures folder
	if (!asteroid.loadFromFile("Textures/asteroid1.png"))
	{
		cout << "ERROR::PLAYER.H::INITTEXTURE::Could not load texture file!" << "\n";
	}

	shape.setTexture(&asteroid);
}

//Constuctors
Enemy::Enemy(float posX, float posY)
{
	initVariables();
	initShape();
	initTexture();
	shape.setPosition(posX, posY);
}

//Distructors
Enemy::~Enemy()
{

}

//Accessors
const FloatRect Enemy::getBounds() const
{
	return shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return points;
}

const int& Enemy::getDamage() const
{
	return damage;
}

//Public functions
void Enemy::update()
{
	shape.move(0.f, speed);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(shape);
}
