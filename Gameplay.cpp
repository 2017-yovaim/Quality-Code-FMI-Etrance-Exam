#include "Gameplay.h"
#include <iostream>

const int R1 = 4; 				const int C1 = 10;
const int R2 = 7;				const int C2 = 17;
const int R3 = 10;				const int C3 = 24;
const int R4 = 13;				const int C4 = 31;
const int R5 = 16;				const int C5 = 38;
const int R6 = 19;				const int C6 = 45;
const int R7 = 22;				const int C7 = 52;
const int R8 = 25;				const int C8 = 59;

const int INVALID_FUNCTION_INPUT = -1;
const int COMMAND_STRING_LENGTH = 10;


Gameplay::Gameplay()
{
}

Gameplay::~Gameplay()
{
}
 
bool Gameplay::isMoveCommandValid(String move)
{
	//example command: move d2 d4 
	if (move.getLength() != COMMAND_STRING_LENGTH) {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	else if (move[0] != 'm' || move[1] != 'o' || move[2] != 'v' || move[3] != 'e' || move[4] != ' ' || move[7] != ' ') {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	else if (move[5] < 'a' || move[5] > 'h' || move[6] < '1' || move[6] > '8' || move[8] < 'a' || move[8] > 'h' || move[9] < '1' || move[9] > '8') {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	return true;
}

int determineLetter(char letter)
{
	switch (letter)
	{
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
	default:
		return 7;

	}
}

int determineNumber(char number)
{
	if (number >= '1' && number <= '8')
	{
		return (int)number - '1';
	}
	return 7;
}

bool cellIsEmpty(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int number, int letter)
{
	return board[number][letter].piece == nullptr;
}

bool isPlayersPiece(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int number, int letter, int player)
{
	if (cellIsEmpty(board, number, letter))
		return false;
	return board[number][letter].piece->getPlayer() == player;
}

bool isKingMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber, int toLetter, 
	int currentPlayer, int rowDifference, int columnDifference, bool& isKingDead)
{
	if (abs(rowDifference) > 1 || abs(columnDifference) > 1) {
		std::cout << "Kings may only move one square" << std::endl;
		return false;
	}
	if (board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() != currentPlayer) {
		std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
		if (board[toNumber][toLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
}

bool isKnightMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber, int toLetter,
	int currentPlayer, int rowDifference, int columnDifference, bool& isKingDead)
{
	if (abs(rowDifference) * abs(columnDifference) != 2) {
		std::cout << "Knights can move only L-shape" << std::endl;
		return false;
	}
	if (board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() != currentPlayer) {
		std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
		if (board[toNumber][toLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
}

bool isPlayer2PawnMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber,
	int toLetter, int rowDifference, int columnDifference, bool& isKingDead)
{
	if (fromNumber != 1 && rowDifference <= -2) {
		std::cout << "Pawns can move 2 squares forward only in their first move" << std::endl;
		return false;
	}
	else if (fromNumber == 1 && rowDifference < -2) {
		std::cout << "Pawns can't move more than 2 squares forward their first move." << std::endl;
		return false;
	}
	else if (rowDifference >= 0) {
		std::cout << "Pawns can only move forward" << std::endl;
		return false;
	}
	else if (abs(columnDifference) > 1) {

		std::cout << "Pawns can't move more than one column forward" << std::endl;
		return false;
	}
	else if (abs(columnDifference) == 1 && rowDifference == -1 && board[toNumber][toLetter].piece == nullptr) {

		std::cout << "There must be an enemy piece on that position for you to move there." << std::endl;;
		return false;
	}
	else if (rowDifference == -1 && columnDifference == 0 && board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() == 1) {
		std::cout << "An enemy piece is blocking your move!" << std::endl;
		return false;
	}
	else if (rowDifference == -1 && abs(columnDifference) == 1 && board[toNumber][toLetter].piece->getPlayer() == 1) {
		std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
		if (board[toNumber][toLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
}

bool isPlayer1PawnMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber,
	int toLetter, int rowDifference, int columnDifference, bool& isKingDead)
{
	if (fromNumber != 6 && rowDifference >= 2) {
		std::cout << "Pawns can move 2 squares forward only in their first move" << std::endl;
		return false;
	}
	else if (fromNumber == 6 && rowDifference > 2) {
		std::cout << "Pawns can't move more than 2 squares forward their first move." << std::endl;
		return false;
	}
	else if (rowDifference <= 0) {
		std::cout << "Pawns can only move forward" << std::endl;
		return false;
	}
	else if (abs(columnDifference) > 1) {
		std::cout << "Pawns can't move more than one column forward" << std::endl;
		return false;
	}
	else if (abs(columnDifference) == 1 && rowDifference == 1 && board[toNumber][toLetter].piece == nullptr) {
		std::cout << "There must be an enemy piece on that position for you to move there." << std::endl;
		return false;
	}
	else if (rowDifference == 1 && columnDifference == 0 && board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() == 2) {
		std::cout << "An enemy piece is blocking your move!" << std::endl;
		return false;
	}
	else if (rowDifference == 1 && abs(columnDifference) == 1 && board[toNumber][toLetter].piece->getPlayer() == 2) {
		std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
		if (board[toNumber][toLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
}

bool isBishopMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber,
	int toLetter, int currentPlayer, int rowDifference, int columnDifference, bool& isKingDead)
{
	if (abs(rowDifference) != abs(columnDifference)) {
		std::cout << "Bishops can move only diagonally" << std::endl;
		return false;
	}
	if (rowDifference > 0 && columnDifference > 0) {
		int a = fromLetter;
		for (int i = fromNumber - 1; i > toNumber; i--) {
			for (a; a > toLetter; a--) {
				a--;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference < 0) {
		int a = fromLetter;
		for (int i = fromNumber + 1; i < toNumber; i++) {
			for (a; a < toLetter; a++) {
				a++;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference > 0 && columnDifference < 0) {
		int a = fromLetter;
		for (int i = fromNumber - 1; i > toNumber; i--) {
			for (a; a < toLetter; a++) {
				a++;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference > 0) {
		int a = fromLetter;
		for (int i = fromNumber + 1; i < toNumber; i++) {
			for (a; a > toLetter; a--) {
				a--;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	if (board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() != currentPlayer) {
		std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
		if (board[toNumber][toLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
}

bool isRookMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber, int toLetter,
	int currentPlayer, int rowDifference, int columnDifference, bool& isKingDead)
{
	if (rowDifference != 0 && columnDifference != 0) {
		std::cout << "Rooks can move only horizontal or vertical" << std::endl;
		return false;
	}
	if (rowDifference == 0 && columnDifference > 0) {
		for (int i = fromLetter - 1; i > toLetter; i--) {
			if (board[fromNumber][i].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference == 0 && columnDifference < 0) {
		for (int i = fromLetter + 1; i < toLetter; i++) {
			if (board[fromNumber][i].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference > 0 && columnDifference == 0) {
		for (int i = fromNumber - 1; i > toNumber; i--) {
			if (board[i][fromLetter].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference == 0) {
		for (int i = fromNumber + 1; i < toNumber; i++) {
			if (board[i][fromLetter].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	if (board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() != currentPlayer) {
		std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
		if (board[toNumber][toLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
		board[fromNumber][fromLetter].piece = nullptr;
		return true;
	}
}

bool isQueenMoveSuccessful(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int fromNumber, int fromLetter, int toNumber, int toLetter,
	int currentPlayer, int rowDifference, int columnDifference, bool& isKingDead)
{
	{
		if (abs(rowDifference) != abs(columnDifference) && rowDifference != 0 && columnDifference != 0) {
			std::cout << "Queens can move like rooks and bishops only" << std::endl;
			return false;
		}
		if (rowDifference > 0 && columnDifference > 0) {
			for (int i = fromNumber - 1; i > toNumber; i--) {
				int a = fromLetter;
				for (a; a > toLetter; a--) {
					a--;
					if (board[i][a].piece != nullptr) {
						std::cout << "There's a piece blocking your move!" << std::endl;
						return false;
					}
					break;
				}
			}
		}
		else if (rowDifference < 0 && columnDifference < 0) {
			int a = fromLetter;
			for (int i = fromNumber + 1; i < toNumber; i++) {
				for (a; a < toLetter; a++) {
					a++;
					if (board[i][a].piece != nullptr) {
						std::cout << "There's a piece blocking your move!" << std::endl;
						return false;
					}
					break;
				}
			}
		}
		else if (rowDifference > 0 && columnDifference < 0) {
			int a = fromLetter;
			for (int i = fromNumber - 1; i > toNumber; i--) {
				a++;
				for (a; a < toLetter; a++) {
					if (board[i][a].piece != nullptr) {
						std::cout << "There's a piece blocking your move!" << std::endl;
						return false;
					}
					break;
				}
			}
		}
		else if (rowDifference < 0 && columnDifference > 0) {
			int a = fromNumber;
			for (int i = fromNumber + 1; i < toNumber; i++) {
				for (a; a > toLetter; a--) {
					a--;
					if (board[i][a].piece != nullptr) {
						std::cout << "There's a piece blocking your move!" << std::endl;
						return false;
					}
				}
			}
		}
		else if (rowDifference == 0 && columnDifference > 0) {
			for (int i = fromLetter - 1; i >= toLetter; i--) {
				if (board[fromNumber][i].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
			}
		}
		else if (rowDifference == 0 && columnDifference < 0) {
			for (int i = fromLetter + 1; i < toLetter; i++) {
				if (board[fromNumber][i].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
			}
		}
		else if (rowDifference > 0 && columnDifference == 0) {
			for (int i = fromNumber - 1; i > toNumber; i--) {
				if (board[i][fromLetter].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
			}
		}
		else if (rowDifference < 0 && columnDifference == 0) {
			for (int i = fromNumber + 1; i < toNumber; i++) {
				if (board[i][fromLetter].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
			}
		}
		if (board[toNumber][toLetter].piece != nullptr && board[toNumber][toLetter].piece->getPlayer() != currentPlayer) {
			std::cout << "You have taken the enemy's " << board[toNumber][toLetter].piece->getName() << "!" << std::endl;
			if (board[toNumber][toLetter].piece->getName() == "King") {
				isKingDead = true;
			}
			board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
			board[fromNumber][fromLetter].piece = nullptr;
			return true;
		}
		else {
			std::cout << "Move successful!" << std::endl;
			board[toNumber][toLetter].piece = board[fromNumber][fromLetter].piece;
			board[fromNumber][fromLetter].piece = nullptr;
			return true;
		}
	}
}

bool Gameplay::canMove(String move, Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD], int currentPlayer) {

	int fromLetter;
	int fromNumber;
	int toLetter;
	int toNumber;

	fromLetter = determineLetter(move[5]);

	toLetter = determineLetter(move[8]);

	fromNumber = determineNumber(move[6]);

	toNumber = determineNumber(move[9]);

	// if the starting position to move a piece is empty
	if (cellIsEmpty(board, fromNumber, fromLetter)) {
		std::cout << "There's no piece at that location." << std::endl << std::endl;
		return false;
	}

		//checks if the piece trying to move is the current player's piece
	if (!isPlayersPiece(board, fromNumber, fromLetter, currentPlayer)) {
		std::cout << "That's not your piece!" << std::endl << std::endl;
		return false;
	}

		//checks if the player has an own piece at the square he is trying to get to
	if (!cellIsEmpty(board, toNumber, toLetter) && isPlayersPiece(board, toNumber, toLetter, currentPlayer)) {
		std::cout << "You already have a piece there." << std::endl;
		return false;
	}

		
	int rowDifference = fromNumber - toNumber;
	int columnDifference = fromLetter - toLetter;
		//player 2 pawn rules
	if (board[fromNumber][fromLetter].piece->getName() == "Pawn"  && currentPlayer == 2) {
		return isPlayer2PawnMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, rowDifference, columnDifference, isKingDead);
	}
	// player 1 pawn rules
	else if (board[fromNumber][fromLetter].piece->getName() == "Pawn" && currentPlayer == 1) {
		return isPlayer1PawnMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, rowDifference, columnDifference, isKingDead);
	}
	else if (board[fromNumber][fromLetter].piece->getName() == "King") {
		return isKingMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, currentPlayer, rowDifference, columnDifference, isKingDead);
	}
	else if (board[fromNumber][fromLetter].piece->getName() == "Queen") {
		return isQueenMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, currentPlayer, rowDifference, columnDifference, isKingDead);
	}
	else if (board[fromNumber][fromLetter].piece->getName() == "Knight") {
		return isKnightMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, currentPlayer, rowDifference, columnDifference, isKingDead);
	}
	else if (board[fromNumber][fromLetter].piece->getName() == "Bishop") {
		return isBishopMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, currentPlayer, rowDifference, columnDifference, isKingDead);
	}
	else if (board[fromNumber][fromLetter].piece->getName() == "Rook") {
		return isRookMoveSuccessful(board, fromNumber, fromLetter, toNumber, toLetter, currentPlayer, rowDifference, columnDifference, isKingDead);
	}
	else 
	{
		return false;
	}
}

/*
void Gameplay::undo(String move,Board board[8][8]) {
	
}
*/

//I cannot for the life of me comprehend these magic numbers
void Gameplay::FillBoard()
{ 
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 65; j++){
			gameField[i][j] = ' ';
		}
	}
}
void Gameplay::PaintBoard()
{
	for (int i = 3; i < 27; i++){
		for (int j = 7; j < 63; j++){
			if ((((i > 2 && i < 6) || (i > 8 && i < 12) || (i > 14 && i < 18) || (i > 20 && i < 24))
				&& ((j > 6 && j < 14) || (j > 20 && j < 28) || (j > 34 && j < 42) || (j > 48 && j < 56))) ||
				(((i > 5 && i < 9) || (i > 11 && i < 15) || (i > 17 && i < 21) || (i > 23 && i < 27))
					&& ((j > 13 && j < 21) || (j > 27 && j < 35) || (j > 41 && j < 49) || (j > 55 && j < 63))))
				gameField[i][j] = 219;
		}
	}
}
void Gameplay::PrintBorders() {
	for (int i = 3; i < 27; i++){
		gameField[i][5] = 186;
		gameField[i][64] = 186;
	}
	gameField[2][5] = 201;
	gameField[2][64] = 187;
	gameField[27][64] = 188;
	gameField[27][5] = 200;
	for (int j = 6; j < 64; j++){
		gameField[2][j] = 205;
		gameField[27][j] = 205;
	}
}
void Gameplay::PrintNumbering()
{
	int k = 0;

	//column nameing
	for (int j = 10; j < 63; j += 7){
		gameField[1][j] = 65 + k;
		k++;

	}
	//line numbering
	for (int i = 4; i < 27; i += 3){{
			gameField[i][3] = 41 + k;
			k++;
		}
	}
}
void Gameplay::FigureSpaceCleaning()
{
	//freeing space for figures
	for (int i = 4; i < 27; i += 3){
		for (int j = 10; j < 63; j += 7){
			gameField[i][j - 1] = '  ';
			gameField[i][j] = '  ';
			gameField[i][j + 1] = '  ';
		}
	}
}

int determineRow(int index)
{
	switch (index)
	{
	case 0:
		return R1;
	case 1:
		return R2;
	case 2:
		return R3;
	case 3:
		return R4;
	case 4:
		return R5;
	case 5:
		return R6;
	case 6:
		return R7;
	case 7:
		return R8;
	default:
		return INVALID_FUNCTION_INPUT;

	}
}

int determineColumn(int index)
{
	switch (index)
	{
	case 0:
		return C1;
	case 1:
		return C2;
	case 2:
		return C3;
	case 3:
		return C4;
	case 4:
		return C5;
	case 5:
		return C6;
	case 6:
		return C7;
	case 7:
		return C8;
	default:
		return INVALID_FUNCTION_INPUT;
	}
}


void Gameplay::PlacePieces(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD])
{
	//Taking the coordinates of where pieces will be placed
	
	int row, col;

	for (int i = 0; i < 8; i++){
		row = determineRow(i);
		for (int j = 0; j < 8; j++){
			col = determineColumn(j);

			if (board[i][j].piece == nullptr) {
				gameField[row][col] = ' ';
			}
			else if (board[i][j].piece->getName() == "Pawn" && board[i][j].piece->getPlayer() == 1) {
				gameField[row][col] = 'P';
			}
			else if (board[i][j].piece->getName() == "King" && board[i][j].piece->getPlayer() == 1) {
				gameField[row][col] = 'K';
			}
			else if (board[i][j].piece->getName() == "Queen" && board[i][j].piece->getPlayer() == 1) {
				gameField[row][col] = 'Q';
			}
			else if (board[i][j].piece->getName() == "Rook" && board[i][j].piece->getPlayer() == 1) {
				gameField[row][col] = 'R';
			}
			else if (board[i][j].piece->getName() == "Knight" && board[i][j].piece->getPlayer() == 1) {
				gameField[row][col] = 'N';
			}
			else if (board[i][j].piece->getName() == "Bishop" && board[i][j].piece->getPlayer() == 1) {
				gameField[row][col] = 'B';
			}
			else if (board[i][j].piece->getName() == "Pawn" && board[i][j].piece->getPlayer() == 2) {
				gameField[row][col] = 'p';
			}
			else if (board[i][j].piece->getName() == "King" && board[i][j].piece->getPlayer() == 2) {
				gameField[row][col] = 'k';
			}
			else if (board[i][j].piece->getName() == "Queen" && board[i][j].piece->getPlayer() == 2) {
				gameField[row][col] = 'q';
			}
			else if (board[i][j].piece->getName() == "Rook" && board[i][j].piece->getPlayer() == 2) {
				gameField[row][col] = 'r';
			}
			else if (board[i][j].piece->getName() == "Knight" && board[i][j].piece->getPlayer() == 2) {
				gameField[row][col] = 'n';
			}
			else if (board[i][j].piece->getName() == "Bishop" && board[i][j].piece->getPlayer() == 2) {
				gameField[row][col] = 'b';
			}
		}
	}
	//printing the board
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 65; j++){
			std::cout << gameField[i][j];
		}
		std::cout << std::endl;
	}
}
void Gameplay::PrintBoard(Cell board[ROWS_IN_BOARD][COLUMNS_IN_BOARD])
{
	FillBoard();
	PrintNumbering();
	PaintBoard();
	FigureSpaceCleaning();
	PrintBorders();
	PlacePieces(board);
}

void Gameplay::PlayGame()
{
	Pawn wP1("Pawn", 1);
	Pawn wP2("Pawn", 1);
	Pawn wP3("Pawn", 1);
	Pawn wP4("Pawn", 1);
	Pawn wP5("Pawn", 1);
	Pawn wP6("Pawn", 1);
	Pawn wP7("Pawn", 1);
	Pawn wP8("Pawn", 1);
	Rook wR1("Rook", 1);
	Rook wR2("Rook", 1);
	Knight wN1("Knight", 1);
	Knight wN2("Knight", 1);
	Bishop wB1("Bishop", 1);
	Bishop wB2("Bishop", 1);
	Queen wQ("Queen", 1);
	King wK("King", 1);

	Pawn bP1("Pawn", 2);
	Pawn bP2("Pawn", 2);
	Pawn bP3("Pawn", 2);
	Pawn bP4("Pawn", 2);
	Pawn bP5("Pawn", 2);
	Pawn bP6("Pawn", 2);
	Pawn bP7("Pawn", 2);
	Pawn bP8("Pawn", 2);
	Rook bR1("Rook", 2);
	Rook bR2("Rook", 2);
	Knight bN1("Knight", 2);
	Knight bN2("Knight", 2);
	Bishop bB1("Bishop", 2);
	Bishop bB2("Bishop", 2);
	Queen bQ("Queen", 2);
	King bK("King", 2);

	board[7][0].piece = &wR1;
	board[7][1].piece = &wN1;
	board[7][2].piece = &wB1;
	board[7][3].piece = &wQ;
	board[7][4].piece = &wK;
	board[7][5].piece = &wB2;
	board[7][6].piece = &wN2;
	board[7][7].piece = &wR2;

	board[6][0].piece = &wP1;
	board[6][1].piece = &wP2;
	board[6][2].piece = &wP3;
	board[6][3].piece = &wP4;
	board[6][4].piece = &wP5;
	board[6][5].piece = &wP6;
	board[6][6].piece = &wP7;
	board[6][7].piece = &wP8;

	board[0][0].piece = &bR1;
	board[0][1].piece = &bN1;
	board[0][2].piece = &bB1;
	board[0][3].piece = &bQ;
	board[0][4].piece = &bK;
	board[0][5].piece = &bB2;
	board[0][6].piece = &bN2;
	board[0][7].piece = &bR2;

	board[1][0].piece = &bP1;
	board[1][1].piece = &bP2;
	board[1][2].piece = &bP3;
	board[1][3].piece = &bP4;
	board[1][4].piece = &bP5;
	board[1][5].piece = &bP6;
	board[1][6].piece = &bP7;
	board[1][7].piece = &bP8;

	int currPlayer = 2; // since we change the current player in the while loop we declare it as 2 so it can become 1
	String comand;

	while (true)
	{
		//after every valid move we will change Current player
		if (currPlayer == 1) {
			currPlayer = 2;
			//std::cout << "from 1 to 2";
		}
		else {
			currPlayer = 1;
			//std::cout << "from 2 to 1";
		}

		PrintBoard(board);

		std::cout << std::endl;
		std::cout << "It is Player " << currPlayer << " turn. Please enter your command:" << std::endl;

		std::cin >> comand;
		if (comand == "help") {
			std::cout << "-----------------Help menu-----------------" << std::endl;
			std::cout << "Possible commands: " << std::endl;
			std::cout << "undo -> returns the game to the state before the last move." << std::endl;
			std::cout << "exit -> exits the game." << std::endl;
			std::cout << "move x1y1 x2y2 -> if possible, move the figure from position (x1, y1) to position (x2, y2)" << std::endl;
			std::cout << "example move command ---> move d2 d4" << std::endl;
			if (currPlayer == 1) {
				currPlayer = 2;
			}
			else {
				currPlayer = 1;
			}
		}
		else if (comand == "undo") {
			
		}
		else if (comand == "exit") {
			break;
		}
		else {
			while (!(isMoveCommandValid(comand)))
			{
				std::cin >> comand;
			}
			while (!(canMove(comand, board, currPlayer)) || (!(isMoveCommandValid(comand))))
			{
				std::cout << "Please enter your move again!" << std::endl;
				std::cin >> comand;
			}
		}
		if (isKingDead) {
			std::cout << "Player " << currPlayer << " wins!" << std::endl;
			break;
		}
	}
}