#include "Tetriminos.h"

int Tetriminos::pickPiece()
{
	// Pick random piece from 0 - 4
	srand(time(NULL));
	return rand() % 5;
}

void Tetriminos::generateTetrimino()
{
	currentSelection = this->pickPiece();
}

Tetriminos::Tetriminos()
{
	geometry = { 
		{0,1,0,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0},
		{0,0,0,0,
		 0,1,1,0,
		 0,1,1,0,
		 0,0,0,0},
		{0,1,0,0,
		 0,1,1,0,
		 0,0,1,0,
		 0,0,0,0},
		{0,0,0,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,1,1,0},
		{0,0,0,0,
		 1,1,1,0,
		 0,1,0,0,
		 0,0,0,0}
	};
}

Tetriminos::~Tetriminos()
{
}

int Tetriminos::getSelection()
{
	return currentSelection;
}

std::vector<int> Tetriminos::getTetrimino()
{
	return geometry[currentSelection];
}
