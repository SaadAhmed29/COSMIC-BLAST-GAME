#include "Enemy.h"

void Enemy::initVariables()
{
	this->type = 0;
	this->speed = 2.0f;
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->damage = 1;
	this->points = 1;
}

void Enemy::initAsteroid()
{
	this->asteroidtext.loadFromFile("rocks.png");
	this->astSprite.setTexture(asteroidtext);
	int x = rand() % 4 + 1;

	switch (x) {
	case 1: {
		this->astSprite.setScale(1.1f, 1.1f);
		this->astSprite.setRotation(180.f);
		break;
	}
	case 2: {
		this->astSprite.setScale(0.4f, 0.4f);
		this->astSprite.setRotation(30.f);
		break;
	}
	case 3: {
		this->astSprite.setScale(0.9f, 0.9f);
		this->astSprite.setRotation(100.f);
		break;
	}
	case 4: {
		this->astSprite.setScale(0.7f, 0.7f);
		break;
	}
	default:
		this->astSprite.setScale(0.f, 0.f);
	}

}

Enemy::Enemy(float pos_x,float pos_y)
{

	
	this->initAsteroid();
	this->initVariables();
	this->astSprite.setPosition(pos_x, pos_y);

}

Enemy::~Enemy()
{

}

//Functions

const sf::FloatRect Enemy::getBounds() const
{
	return this->astSprite.getGlobalBounds();
}

const sf::Vector2f Enemy::getScale() const
{
	return this->astSprite.getScale();
}

const int& Enemy::getPoints() const
{
	return this->points;
}


void Enemy::update()
{
	//ASTEROID SPEED
	
	this->astSprite.move(0.f, this->speed);
	
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->astSprite);
}

void Enemy::EnemyRotate()
{
	//astSprite.setOrigin(astSprite.getLocalBounds().width / 2.0f, astSprite.getLocalBounds().height / 2.0f);
	if (this->astSprite.getScale().x >= 0.9f) {
		this->astSprite.rotate(0.2f);
	}
	else
		this->astSprite.rotate(-0.4f);
}




