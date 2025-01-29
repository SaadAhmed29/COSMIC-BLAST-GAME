#ifndef ENEMY_H
#endif // !ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
using namespace sf;
using namespace std;

class Enemy
{
private:
	Texture asteroidtext;
	Sprite astSprite;
	int hp;
	int hpMax;
	int damage;
	int points;
	int type;
	float speed;
	IntRect rectSourceAsteroid;

	void initVariables();
	void initAsteroid();


public:
	Enemy(float pos_x, float pos_y);
	~Enemy();


	//Accessors
	
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getScale() const;
	const int& getPoints() const;

	//Functions
	void update();
	void render(RenderTarget* target);
	void EnemyRotate();
	
};

