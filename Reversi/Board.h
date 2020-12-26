#pragma once
#define EMPTY 0
#define BLACK 1
#define WHITE 2

//its parent class, use it as a pointer to avoid circular reference
class Reversi;

class Board
{
public:
	Board();
	
	void initialize();
	void draw();
	
	char table[8][8];
	int black_num;
	int white_num;
	Reversi* reversi;
};

