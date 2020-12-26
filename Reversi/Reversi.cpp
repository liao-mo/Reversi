#include <iostream>
#include "Reversi.h"
#include "Board.h"

using namespace std;

Reversi::Reversi(void)
{
	initialize();
}


void Reversi::initialize() {
	nowTurn = BLACK;
	isEnd = false;
	board = new Board;
	board->reversi = this;
	for (int i = 0; i < 8; i++)
	{
		buttonAtoH[i] = false;
		button1to8[i] = false;
	}
}

void Reversi::updataScreen() {
	system("cls");
	board->draw();

	//Turn tip
	cout << endl << "Your turn¡G";
	if (nowTurn == BLACK)
		cout << "¡´" << endl;
	else if (nowTurn == WHITE)
		cout << "¡³" << endl;

	cout << endl;
	//Key tips
	//cout << "NewGame¡G\tEnter" << endl;

	//check if someone has won the game
	if (board->black_num == 0 || board->white_num == 0 || board->black_num + board->white_num == 64)
		isEnd = true;
	else
		isEnd = false;

	//Winner tip
	if (isEnd)
	{
		if (board->black_num > board->white_num)
			cout << "¡´ Win!" << endl;
		else if (board->black_num < board->white_num)
			cout << "¡³ Win!" << endl;
		else
			cout << "It's a draw." << endl;
	}
}

void Reversi::buttonPressed() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//if we hit a alphabet and a number, then try to place a piece on the board
			if (buttonAtoH[i] && button1to8[j])
			{
				place(i, j);
				return;
			}
		}
	}
}

void Reversi::place(int i, int j) {
	bool placeFlag = false;
	if (board->table[i][j] != EMPTY) return;
	else
	{
		placeFlag |= canPlay(i, j, -1, -1, true, true);
		placeFlag |= canPlay(i, j, 0, -1, true, true);
		placeFlag |= canPlay(i, j, 1, -1, true, true);
		placeFlag |= canPlay(i, j, -1, 0, true, true);
		placeFlag |= canPlay(i, j, 1, 0, true, true);
		placeFlag |= canPlay(i, j, -1, 1, true, true);
		placeFlag |= canPlay(i, j, 0, 1, true, true);
		placeFlag |= canPlay(i, j, 1, 1, true, true);
	}
	if (placeFlag)
	{
		board->table[i][j] = nowTurn;
		switchPlayer();
		if (canPlayAny() == false)	//someone can not play any piece
			switchPlayer();
		updataScreen();
	}
}

void Reversi::switchPlayer() {
	if (nowTurn == BLACK) nowTurn = WHITE;
	else nowTurn = BLACK;
}

bool Reversi::canPlay(int x, int y, int deltaX, int deltaY, bool isFirst, bool play) {
	x += deltaX;
	y += deltaY;
	if (x < 0 || x>7 || y < 0 || y > 7) return false;

	if (isFirst)
	{
		if (board->table[x][y] == nowTurn)
			return false;
		else if (board->table[x][y] == 0)
			return false;
		else if (canPlay(x, y, deltaX, deltaY, false, play))
		{
			if(play)
				board->table[x][y] = nowTurn;
			return true;
		}
		else
			return false;
	}
	else
	{
		if (board->table[x][y] == nowTurn)
		{
			if (play)
				board->table[x][y] = nowTurn;
			return true;
		}
		else if (board->table[x][y] == 0)
			return false;
		else if (canPlay(x, y, deltaX, deltaY, false, play))
		{
			if (play)
				board->table[x][y] = nowTurn;
			return true;
		}
		else
			return false;
	}
}

bool Reversi::canPlayAny() {
	bool placeFlag = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board->table[i][j] != 0)
			{
				continue;
			}
			placeFlag |= canPlay(i, j, -1, -1, true, false);
			placeFlag |= canPlay(i, j, 0, -1, true, false);
			placeFlag |= canPlay(i, j, 1, -1, true, false);
			placeFlag |= canPlay(i, j, -1, 0, true, false);
			placeFlag |= canPlay(i, j, 1, 0, true, false);
			placeFlag |= canPlay(i, j, -1, 1, true, false);
			placeFlag |= canPlay(i, j, 0, 1, true, false);
			placeFlag |= canPlay(i, j, 1, 1, true, false);
		}
	}
	return placeFlag;
}