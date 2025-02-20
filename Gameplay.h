#pragma once
#include "Cell.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

const int ROWS_IN_BOARD = 8;
const int COLUMNS_IN_BOARD = 8;

class Gameplay {
public:
	Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD];
	char gameField[28][65];
	bool isKingDead = false;
	Gameplay();
	~Gameplay();
	void PlayGame();
	bool isMoveCommandValid(String move);
	bool canMove(String move, Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int currentPlayer);
	void FillBoard();
	void PaintBoard();
	void PrintBorders();
	void PrintNumbering();
	void FigureSpaceCleaning();
	void PlacePieces(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD]);
	void PrintBoard(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD]);
	//void undo(String move, Board board[8][8]);

};


