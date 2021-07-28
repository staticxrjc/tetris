#include "GameEngine.h"
#include <iostream>
#include "SFML/Audio/Music.hpp"


//Private Functions
void GameEngine::initVariables()
{
	this->window = nullptr;
	gameBoard =
	{
		1,9,9,9,9,9,9,9,9,9,9,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1
	};
	finalRender = gameBoard;
	
	//Set game status to running
	gameStatus = 0;

	//Set score to 0
	score = 0;

	//Set Level to 0
	level = 0;

	//Starts Timer
	start = std::chrono::high_resolution_clock::now();
}

void GameEngine::initWindow()
{
	this->videoMode.height = 420;
	this->videoMode.width = 300;
	this->window = new sf::RenderWindow(this->videoMode, "Tetris - SFML", sf::Style::Titlebar | sf::Style::Close);
}

int GameEngine::checkCollision(int i, std::vector<int> reference)
{
	if (finalRender[reference[i]] != 0 && finalRender[reference[i]] != 9) {
		this->player.undoControl();
		return 1;
	}
	return 0;
}

void GameEngine::renderPlayer()
{
	// This Function Copies the Gameboard (to keep it static) and adds the 
	// Player on top of it, while it does this it checks for collisions.
	finalRender = gameBoard;
	
	// These two variables are used to orientate the selection with the Gameboard
	std::vector<int> CurrentSel = this->player.getCurrentSel();
	std::vector<int> indexReference = this->player.getTrueIndices(12);
	
	int i;
	for (int x=0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			i = y * 4 + x;

			// Writing to array based on player angle, if there is collission revert
			switch (this->player.getPlayerA()) {
			case 0:
				if (CurrentSel[i] == 1) {
					if (checkCollision(i, indexReference)) {
						return;
					}
					finalRender[indexReference[i]] = CurrentSel[i];
				}
				break;
			case 90:
				if (CurrentSel[y + 12 - (x * 4)] == 1) {
					if (checkCollision(i, indexReference)) {
						return;
					}
					finalRender[indexReference[i]] = CurrentSel[y + 12 - (x * 4)];
				}
				break;
			case 180:
				if (CurrentSel[(15 - y * 4) - x] == 1) {
					if (checkCollision(i, indexReference)) {
						return;
					}
					finalRender[indexReference[i]] = CurrentSel[(15 - y * 4) - x];
				}
				break;
			case 270:
				if (CurrentSel[(3 - y) + 4 * x] == 1) {
					if (checkCollision(i, indexReference)) {
						return;
					}
					finalRender[indexReference[i]] = CurrentSel[(3 - y) + 4 * x];
				}
				break;
			}
		}
	}

}

//Constructors & Destructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();
}

GameEngine::~GameEngine()
{
	delete this->window;
}

int GameEngine::rowCheck(std::vector<int> board)
{
	// check from position end of vector -> 12 (backwords)
	// incrementing 12 at a time and
	// if match 111111111111 is found, shift the vector
	// and add 1 as a return
	int matches = 0;
	std::vector<int> solidBlock = { 1,1,1,1,1,1,1,1,1,1,1,1 };
	std::vector<int> emptyBlock = { 1,0,0,0,0,0,0,0,0,0,0,1 };
	for(int i = 12; i < board.size() - 12; i = i + 12)
		if (std::equal(solidBlock.begin(), solidBlock.end(), board.begin() + i))
		{
			printf("Match Found at %i!\n", i);
			gameBoard.erase(gameBoard.begin() + i, gameBoard.begin() + i + 12);
			gameBoard.insert(gameBoard.begin() + 12, emptyBlock.begin(), emptyBlock.end());
			matches++;
		}
	switch (matches) {
	case 1:
		return 40;
		break;
	case 2:
		return 100;
		break;
	case 3:
		return 300;
		break;
	case 4:
		return 1200;
		break;
	}
	return 0;
}

sf::VertexArray GameEngine::tileSet(std::vector<int> mapArray, int columns, int length)
{
	// Define the quads points
	// 2d char Array 'X' is white (block) '.' is black (non-block)
	// index and number of columns in the array will be used to determine x/y coordinates
	// Array[x,y] = [index % column][(index - (index % column)) / columns]
	// 
	// 	   (0,0) is the top left corner
	// 
	// 	      X=0, X=1, X=2, X=3
	// 	  Y=0, 0	0	 0	  0
	// 	  Y=1, 0	0	 0	  0
	// 	  Y=2, 0	0	 0	  0
	// 	  Y=3, 0	0	 0    0
	// 
	// x = index % column
	// y = (index - (x)) / columns

	sf::VertexArray quads(sf::Quads, length*4);
	
	for (int i = 0; i < length; i++)
	{
		//Defining x,y coordinates
		int x = i % columns;
		int y = (i - x) / columns;

		//Defining Block Size & Corners
		float bSize = 15.f;

		//Populating the Map
		quads[(i*4)+0].position = sf::Vector2f((float)x * bSize,(float)y * bSize);
		quads[(i*4)+1].position = sf::Vector2f((float)x * bSize,(float)y * bSize + bSize - 1.f);
		quads[(i*4)+2].position = sf::Vector2f((float)x * bSize + bSize - 1.f,(float)y * bSize + bSize - 1.f);
		quads[(i*4)+3].position = sf::Vector2f((float)x * bSize + bSize - 1.f,(float)y * bSize);
		
		sf::Color fill = sf::Color::Black;
		//Setting filled or unfilled color
		if (mapArray[i] == 1 || mapArray[i] == 9)
		{
			fill = sf::Color::White;
		}
		quads[(i * 4) + 0].color = fill;
		quads[(i * 4) + 1].color = fill;
		quads[(i * 4) + 2].color = fill;
		quads[(i * 4) + 3].color = fill;

	}

	return quads;
}

//Accessors
bool GameEngine::running()
{
	return this->window->isOpen();
}

void GameEngine::pollEvents()
{
	while (this->window->pollEvent(this->evnt))
	{
		switch (this->evnt.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::TextEntered:
			if (this->evnt.text.unicode < 128 && gameStatus == 0)
			{
				if (this->evnt.text.unicode != 'w' && this->evnt.text.unicode != 's') {
					this->player.controlPlayer(evnt.text.unicode);
				}
				else if (this->evnt.text.unicode == 's') {
					if (this->player.controlPlayer('s', gameBoard, 1)) {
						this->nextCycle();
					};
				}
			}
		}
	}

}

int GameEngine::timedLoop()
{
	if (gameStatus == 1) {
		return 1;
	}
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	if (duration.count() > (pow(0.8f,level+1)))
	{
		start = std::chrono::high_resolution_clock::now();
		printf("%f s\n", duration.count());
		if (this->player.controlPlayer('s', gameBoard, 1)) {
			this->nextCycle();
			return 0;
		}
	}
	return 1;
}

void GameEngine::update()
{
	if (this->timedLoop()) {
		this->pollEvents();
	}
}

void GameEngine::nextCycle()
{
	// Update Gameboard
	gameBoard = finalRender;

	// Increase Level

	// Tally Gameboard (move solid rows down)
	score = score + this->rowCheck(gameBoard);

	// Create new piece
	if (this->player.refresh(gameBoard)) {
		// GAME OVER
		gameStatus = 1;
		printf("game over!\n");
	}
}

void GameEngine::render()
{
	this->window->clear();


	//Draw Player
	this->renderPlayer();

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		printf("Failed font load.");
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::White);

	//Draw Game
	
	board = tileSet(finalRender, 12, gameBoard.size());
	this->window->draw(board);
	if (gameStatus == 1) {
		text.setString("Game Over!\nFinal Score: " + std::to_string(score));
		this->window->clear();
		this->window->draw(text);
	}
	else if (gameStatus == 0)
	{
		text.setString("Score " + std::to_string(score));
		text.setPosition(2, 330);
		this->window->draw(board);
		this->window->draw(text);
	}

	this->window->display();
}
