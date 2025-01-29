#include "Game.h"
#include"Player.h"
#include<SFML/Graphics.hpp>
#include<map>
using namespace sf;

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(800, 600), "COSMIC BLAST");
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player();
}

//Textures
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("laserBullet(1).png");
}

void Game::initGUI()
{
	//Load font

	if (!this->font.loadFromFile("Amatic-Bold.ttf")) {
		cout << "ERROR!! COULD NOT LOAD FONT." << endl;
	}
	//Game Over
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(70);
	this->gameOverText.setFillColor(Color::White);
	this->gameOverText.setPosition(310,260);
	this->gameOverText.setString("GAME OVER!");

	//Restart game text
	this->restartgame.setFont(this->font);
	this->restartgame.setCharacterSize(20);
	this->restartgame.setFillColor(Color::White);
	this->restartgame.setPosition(350, 340);
	this->restartgame.Bold;
	this->restartgame.setString("\"PRESS ENTER TO RESTART\"");

	//Initialize point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(32);
	this->pointText.setFillColor(Color::White);
	this->pointText.setPosition(720, 12);
	this->HpText.setFont(this->font);
	this->HpText.setCharacterSize(22);
	this->HpText.setFillColor(Color::White);
	this->HpText.setPosition(10, 3);
	this->HpText.setString("HEALTH BAR:");
	this->HpText.Bold;

	//Init Player GUI
	this->playerHpBar.setSize(Vector2f(250.f, 20.f));
	this->playerHpBar.setFillColor(Color::White);
	this->playerHpBar.setPosition(Vector2f(10.f, 30.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(Color(25, 25, 25,100));

	//Main menu
	mainmenu.loadFromFile("Mainmenu.jpg");
	Main.setTexture(mainmenu);
	
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::updatePollEvents()
{
	Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == Event::Closed) {
			this->window->close();
		}
	}
}

void Game::initSounds()
{

	bulletBuffer.loadFromFile("laser.wav");
	bulletSound.setBuffer(bulletBuffer);
	CollBuffer.loadFromFile("asteroidcollision.wav");
	Collision.setBuffer(CollBuffer);
	bgbuffer.loadFromFile("backgroundmusic (2).wav");
	bgmusic.setBuffer(bgbuffer);
	gobuffer.loadFromFile("gameover.wav");
	gameover.setBuffer(gobuffer);
	
}

//Functions
void Game::run()
{
	gameState state = gameState::MainMenu;

	while (this->window->isOpen()) {
		this->updatePollEvents();

		switch (state) {
		case gameState::MainMenu:
			this->window->clear();  
			this->window->draw(Main);
			this->window->display();

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				state = gameState::Playing;
				this->bgmusic.play();
			}
			break;

		case gameState::Playing:

			this->window->clear();

			if (this->player->getHp() > 0) {
				this->update();  
			}
			else {
				state = gameState::GameOver;
				this->gameover.play();
			}

			this->render();  
			break;

		case gameState::GameOver:
			
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				this->resetGame();
				this->bgmusic.play();
				state = gameState::Playing;
			}
			break;
		}
	}
}

void Game::resetGame() {
	
	this->window->clear();
	this->points = 0;
	this->player->setHp(100);
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(Vector2f(250.f * hpPercent, this->playerHpBar.getSize().y));

}

void Game::update()
{
	
	
	//Move Player
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		this->player->move(-1.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		this->player->move(1.0f, 0.0f);
	}
	this->player->ScreenWrap();
	this->player->update();

	//Bullet Shooting
	if (Keyboard::isKeyPressed(Keyboard::Space)&&this->player->canAttack()) 
	{
		this->BulletSound();
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getpos().x+14, 
		this->player->getpos().y - 10, 0.f, -1.f, 4.f));
	}
	
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
}


void Game::render()
{
	this->window->clear();

	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game Over text display

	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
		this->window->draw(this->restartgame);
		this->bgmusic.stop();
	}
	this->window->display();

	
}

void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets) {
		bullet->update();

		//Bullet removing when out of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;

	}
}

void Game::updateEnemies()
{
	//AMOUNT OF ASTEROIDS
	if (this->points <= 15) {
		this->spawnTimer += 0.9f;
	}
	else if (this->points > 15 && this->points <= 40) {
		this->spawnTimer += 1.7f;
	}
	else if (this->points > 40 && this->points <= 60) {
		this->spawnTimer += 2.3f;
	}
	else
		this->spawnTimer += 3.f;


	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand() % 750-50+1+50, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;

	for (auto* enemy : this->enemies) {
		enemy->update();
		enemy->EnemyRotate();


		//Enemy removing when out of screen
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		//ENEMY HITTING SHIP
		else if (enemy->getBounds().intersects(this->player->getBounds())) 
		{
			this->CollisionSound();
			//LOSING HP AFTER GETTING HIT
			if (this->enemies.at(counter)->getScale().x < 0.5f) {
				this->player->loseHp(8);
			}
			else if (this->enemies.at(counter)->getScale().x > 0.5f && this->enemies.at(counter)->getScale().x < 1.f) {
				this->player->loseHp(12);
			}
			else if (this->enemies.at(counter)->getScale().x > 1.f) {
				this->player->loseHp(16);
			}

			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

		}

		++counter;

	}
	
}

void Game::updateCombat()
{
	for (int i = 0;i < this->enemies.size();i++)
	{
		bool enemy_deleted = false;

		for (size_t k = 0;k < this->bullets.size() && enemy_deleted==false;k++) 
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())&&this->enemies[i]->getScale().x<1.f)
			{

				this->CollisionSound();
				//POINTS FOR SMALLEST ENEMIES
				if (this->enemies[i]->getScale().x < 0.5f) {
					this->points += this->enemies[i]->getPoints();
				}
				//POINTS FOR NORMAL ENEMIES
				if (this->enemies[i]->getScale().x > 0.5f&& this->enemies[i]->getScale().x<1.f) {
					this->points += this->enemies[i]->getPoints() + 1;
				}

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				enemy_deleted = true;
			}
			else if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()) && this->enemies[i]->getScale().x > 1.f)
			{
				this->CollisionSound();
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

			}
		}
	}
}

void Game::updateGUI()
{
	stringstream ss, Hb;
	ss <<"SCORE: "<< this->points;
	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(Vector2f(250.f*hpPercent, this->playerHpBar.getSize().y));
}

void Game::renderGUI()
{

	this->window->draw(pointText);
	this->window->draw(HpText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);

}

void Game::BulletSound()
{
	this->bulletSound.play();
}

void Game::CollisionSound()
{
	this->Collision.play();
}



Game::Game() {
	this->initWindow();
	this->initPlayer();
	this->initTextures();
	this->initEnemies();
	this->initGUI();
	this->initSystems();
	this->initSounds();
}

Game::~Game() {
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures) {
		delete i.second;
	}
	//Delete Bullets
	for (auto* i : this->bullets) {
		delete i;
	}
	//Delete Enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}
