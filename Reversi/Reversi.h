#pragma once
#define EMPTY 0
#define BLACK 1
#define WHITE 2

class Board;

class Reversi
{
public:
	Reversi();
	void initialize();
	void updataScreen();
	void buttonPressed();
	void place(int i, int j);
	void switchPlayer();
	bool canPlay(int x, int y, int deltaX, int deltaY, bool isFirst, bool play);	//check 8 directions that if we can place this piece.
	bool canPlayAny();

	Board* board;
	int nowTurn;
	bool isEnd;
	bool buttonAtoH[8], button1to8[8];	//key event bool.
};

