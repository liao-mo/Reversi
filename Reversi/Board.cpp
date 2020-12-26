#include <iostream>
#include "Board.h"
#include "Reversi.h"

using namespace std;

Board::Board() {
	initialize();
}

void Board::initialize() {
	//new game initialization
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			table[i][j] = EMPTY;
		}
	}

	black_num = 0;
	white_num = 0;
	reversi = nullptr;

	//Set the four pieces at game start.
	table[3][3] = BLACK;
	table[4][4] = BLACK;
	table[3][4] = WHITE;
	table[4][3] = WHITE;

}

void Board::draw() {
	black_num = 0;
	white_num = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (table[i][j] == EMPTY)
				cout << "¡Ð";
			else if (table[i][j] == BLACK)
			{
				cout << "¡´";
				black_num++;
			}
			else if (table[i][j] == WHITE)
			{
				cout << "¡³";
				white_num++;
			}
		}
		cout << char('A' + i) << " " << reversi->buttonAtoH[i] << endl;
	}
	cout << "1 2 3 4 5 6 7 8" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << reversi->button1to8[i] << " ";
	}
	cout << endl << endl;

	cout << "¡´¡G" << black_num << "  ¡³¡G" << white_num << endl;
}