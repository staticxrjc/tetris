#pragma once
#include <iostream>
#include <vector>
#include "Tetriminos.h"

class Player
{
private:
	// Private Variables
	// Player X Position, Y Position, Angle, Current/Next Tetris Pieces
	Tetriminos tetrimino;
	int playerX;
	int playerY;
	int playerA;
	char lastCommand;
	char undoCommand;
	std::vector<int> currentSel;
	std::vector<int> nextSel;

	// Initializes Variables
	void initVariables();
	int arrayCompare(std::vector<int>);

public:
	// Cosntructor & Destructor
	Player();
	virtual ~Player();

	// Gameplay
	void refresh();
	int refresh(std::vector<int>);

	// Retrieval Functions
	int getPlayerX();
	int getPlayerY();
	int getPlayerA();
	char getLastCommand();
	std::vector<int> getTrueIndices(int);
	std::vector<int> getCurrentSel();
	std::vector<int> getNextSel();

	// Checking Functions
	int checkCollision(int);

	// Control Function
	void undoControl();
	int controlPlayer(char, std::vector<int> = { 0 }, int = 0);
};

