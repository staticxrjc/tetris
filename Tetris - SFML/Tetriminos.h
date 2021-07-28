#pragma once
#include <iostream>
#include <vector>
#include <time.h>

class Tetriminos
{
private:
	// 5 Tetriminos wich unique colors and Selections
	std::vector<std::vector<int>> geometry;
	int currentSelection;
	int pickPiece();

public:
	void generateTetrimino();
	Tetriminos();
	virtual ~Tetriminos();

	// Retrieval Functions
	int getSelection();
	std::vector<int> getTetrimino();
};

