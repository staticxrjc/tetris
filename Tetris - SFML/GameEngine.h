#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include <chrono>

/*
	Game Engine Class
*/

class GameEngine
{
private:
	//Timer
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	
	//Variables
	// 	   Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event evnt;

	//		Map / Board
	sf::VertexArray board;
	std::vector<int> gameBoard;

	//		Player
	Player player;
	int level;

	//		Game Status
	// 0, running
	// 1, game over
	int gameStatus;
	int score;

	//		Final Render
	std::vector<int> finalRender;

	//Private Functions
	void initVariables();
	void initWindow();
	int checkCollision(int, std::vector<int>);
	void renderPlayer();
	int rowCheck(std::vector<int>);
	sf::VertexArray tileSet(std::vector<int>, int, int);

public:
	//Constructors & Destructors
	GameEngine();
	virtual ~GameEngine();

	//Accessors
	bool running();

	//Functions
	void nextCycle();
	void pollEvents();
	int timedLoop();
	void update();
	void render();
};

