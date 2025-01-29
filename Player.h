#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;

static IntRect rectSourceSprite(0, 0, 50, 100);

class Player
{
protected: 
	Clock clock;
	Texture sptexture;
	Texture bgtexture;
	Sprite sprite;
	Sprite bgsprite;
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;
	void initVariables();

	int hp;
	int hpMax;
	

public:

	Player();
	~Player();

	const sf::Vector2f& getpos() const;
	void move(const float dir_x, const float dir_y);
	void initTexture();
	void initSprite();
	void update();
	void render(RenderTarget& target);
	void ScreenWrap();
	void updateAttack();
	const bool canAttack();
	FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	void setHp(const int hp);
	void loseHp(const int value);

};


