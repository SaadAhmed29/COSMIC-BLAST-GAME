#include "Bullet.h"

Bullet::Bullet(){

}

Bullet::Bullet(Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y,float movement_speed)
{
	this->bullet.setTexture(*texture);
	this->bullet.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->bullet.setScale(0.3f, 0.3f);
}

Bullet::~Bullet() {

}

void Bullet::update()
{
	//Movement
	this->bullet.move(this->movementSpeed * this->direction);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->bullet);
}

FloatRect Bullet::getBounds() const
{
	return this->bullet.getGlobalBounds();
}
