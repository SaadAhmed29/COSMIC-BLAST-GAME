#include "Player.h"

void Player::initVariables()
{
	//PLAYER MOVING SPEED AND AMOUNT OF BULLETS
	this->movementSpeed = 1.3f;
	this->attackCooldownMax =30.f;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 100;
	this->hp = this->hpMax;
}



Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}



const sf::Vector2f& Player::getpos() const
{
	return this->sprite.getPosition();
}

void Player::move(const float dir_x, const float dir_y)
{
	this->sprite.move(this->movementSpeed*dir_x,this->movementSpeed*dir_y);
	
}

void Player::initTexture()
{
	this->sptexture.loadFromFile("spaceship final.png");
	this->bgtexture.loadFromFile("background(1).png");
}

void Player::initSprite()
{
	//Background sprite
	this->bgsprite.setTexture(this->bgtexture);
	//Resize sprite

	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = 50;
	rectSourceSprite.height = 95;
	this->sprite.setTexture(this->sptexture);
	this->sprite.setTextureRect(rectSourceSprite);
	this->sprite.scale(0.75f, 0.7f);
	this->sprite.setPosition(400, 500);
	float x, y;
	x = 800 / bgsprite.getGlobalBounds().width;
	y = 600 / bgsprite.getGlobalBounds().height;
	bgsprite.setScale(x, y);
	
}

void Player::update()
{
	//Sprite Frame changing

	if (clock.getElapsedTime().asSeconds() > 0.1f) {
		if (rectSourceSprite.left == 150) {
			rectSourceSprite.left = 0;
		}
		else {
			rectSourceSprite.left += 50;
		}
		this->sprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
	this->updateAttack();
}

void Player::render(RenderTarget& target)
{
	
	target.draw(this->bgsprite);
	target.draw(this->sprite);

}

void Player::ScreenWrap()
{
	if (sprite.getPosition().x >= 810) {
		sprite.setPosition(-20, 500);
	}
	else if (sprite.getPosition().x <= -20) {
		sprite.setPosition(800, 500);
	}
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}
