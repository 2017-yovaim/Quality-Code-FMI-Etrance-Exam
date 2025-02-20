#pragma once
#include "Piece.h"

class Pawn :public Piece {
public:
	Pawn() :Piece(){}
	Pawn(const String name, const int player) :Piece(name, player) {}
};
