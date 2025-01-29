#include<SFML/Graphics.hpp>
#include"Game.h"
#include"Player.h"
#include<map>
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
using namespace sf;

int main() {

	srand(time(0));

	Game game;

	game.run();

}