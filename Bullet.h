#ifndef BULLET_H
#endif // !BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;


class Bullet
{
private:

	Sprite bullet;
	Vector2f direction;
	float movementSpeed;

public:

	Bullet();

	Bullet(Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
		
	
	~Bullet();

	void update();
	void render(RenderTarget* target);
	FloatRect getBounds() const;

};

