#include "bullet.h"

//Constructors
Bullet::Bullet()
{

}

Bullet::Bullet(Texture* texture, float posX, float posY, float dirX, float dirY, float speed)
{
	shape.setTexture(*texture);
	shape.scale(0.5f, 0.5f);
	shape.setPosition(posX, posY);
	direction.x = dirX;
	direction.y = dirY;
	movementSpeed = speed;
}

//Distructors
Bullet::~Bullet()
{

}

//Accessors
const FloatRect Bullet::getBounds() const
{
	return shape.getGlobalBounds();
}

//Public functions
void Bullet::update()
{
	//Laser movement
	shape.move(movementSpeed * direction);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(shape);
}
