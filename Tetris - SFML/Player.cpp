#include "Player.h"


// Initialize Variables
void Player::initVariables()
{
	this->refresh();
	playerA = 0;
	playerX = 5;
	playerY = 0;
}

int Player::arrayCompare(std::vector<int> comparitor)
{
	std::vector<int> indexReference = this->getTrueIndices(12);
	int i;
	for (int x=0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			i = y * 4 + x;

			// Writing to array based on player angle, if there is collission revert
			switch (this->getPlayerA()) {
			case 0:
				if (currentSel[i] == 1) {
					if (checkCollision(comparitor[indexReference[i]])) {
						printf("Collision, %i, %c\n", i, this->getLastCommand());
						printf("RETURN 1\n");
						return 1;
					}
				}
				break;
			case 90:
				if (currentSel[y + 12 - (x * 4)] == 1) {
					if (checkCollision(comparitor[indexReference[i]])) {
						printf("Collision, %i, %c\n", i, this->getLastCommand());
						printf("RETURN 1\n");
						return 1;
					}
				}
				break;
			case 180:
				if (currentSel[(15 - y * 4) - x] == 1) {
					if (checkCollision(comparitor[indexReference[i]])) {
						printf("Collision, %i, %c\n", i, this->getLastCommand());
						return 1;
					}
				}
				break;
			case 270:
				if (currentSel[(3 - y) + 4 * x] == 1) {
					if (checkCollision(comparitor[indexReference[i]])) {
						printf("Collision, %i, %c\n", i, this->getLastCommand());
						return 1;
					}
				}
				break;
			}
		}
	}
	return 0;
}

Player::Player()
{
	this->initVariables();
}

Player::~Player()
{
}

void Player::refresh()
{
		this->tetrimino.generateTetrimino();
		currentSel = this->tetrimino.getTetrimino();
		playerA = 0;
		playerX = 5;
		playerY = 0;
}

int Player::refresh(std::vector<int> gameBoard)
{
	this->refresh();
	// Checks if collission, if no collission return 1
	if (this->arrayCompare(gameBoard)) {
		return 1;
	}
	return 0;
}

int Player::getPlayerX()
{
	return playerX;
}

int Player::getPlayerY()
{
	return playerY;
}

int Player::getPlayerA()
{
	return playerA;
}

char Player::getLastCommand()
{
	return lastCommand;
}

//Returns true index position in map
std::vector<int> Player::getTrueIndices(int columns)
{
	std::vector<int> trueIndices;
	// Returns an array that has relative coordiates for the map
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			trueIndices.push_back((playerY + y) * columns + (playerX + x));
		}
	}
	return trueIndices;
}

std::vector<int> Player::getCurrentSel()
{
	return currentSel;
}

std::vector<int> Player::getNextSel()
{
	return nextSel;
}

int Player::checkCollision(int colValue)
{
	printf("%i\n", colValue);
	if (colValue != 0 && colValue != 9) {
		printf("Collision\n");
		this->undoControl();
		return 1;
	}
	return 0;
}

void Player::undoControl()
{
	this->controlPlayer(undoCommand);
}

int Player::controlPlayer(char command, std::vector<int> comparitor, int compFlag)
{
	lastCommand = command;
	switch (command) {
	case 'a':
		playerX = playerX - 1;
		undoCommand = 'd';
		break;
	case 's':
		playerY = playerY + 1;
		undoCommand = 'w';
		break;
	case 'd':
		playerX = playerX + 1;
		undoCommand = 'a';
		break;
	case 'e':
		playerA = playerA + 90;
		if (playerA > 270) {
			playerA = 0;
		}
		undoCommand = 'q';
		break;
	case 'q':
		playerA = playerA - 90;
		if (playerA < 0) {
			playerA = 270;
		}
		undoCommand = 'e';
		break;
	case 'w':
		playerY = playerY - 1;
		undoCommand = 's';
		break;
	}

	if (compFlag == 1) {
		if (this->arrayCompare(comparitor))
		{
			return 1;
		}
	}
	return 0;
}
