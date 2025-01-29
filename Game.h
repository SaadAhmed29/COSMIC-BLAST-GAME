#pragma once

#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include<map>
#include<string>
#include<sstream>
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;

class Game
{
private:

	//MENU

	Texture mainmenu;
	Sprite Main;

	RenderWindow* window;

	//Player
	Player *player;

	//PlayerGUI
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;


	//Asteroids
	vector<Enemy*>enemies;
	float spawnTimer;
	float spawnTimerMax;

	//Resources
	map<string, Texture*> textures;
	vector<Bullet*> bullets;

	//GUI
	Font font;
	Text pointText;
	Text HpText;
	Text gameOverText;
	Text restartgame;

	//Sound

	Sound bulletSound;
	SoundBuffer bulletBuffer;
	Sound Collision;
	SoundBuffer CollBuffer;
	Sound bgmusic;
	SoundBuffer bgbuffer;
	Sound gameover;
	SoundBuffer gobuffer;

	//Systems
	unsigned points;

	void initWindow();
	void initPlayer();
	void initTextures();
	void initGUI();
	void initEnemies();
	void initSystems();
	void updatePollEvents();
	void initSounds();


public:

	Game();
	~Game();

	void run();

	void update();
	void render();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateGUI();
	void renderGUI();
	void resetGame();

	//Sound Functions
	void BulletSound();
	void CollisionSound();


	enum class gameState { MainMenu, Playing, GameOver };

};


