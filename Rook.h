#pragma once
#include "Piece.h"

class Rook :public Piece {
public:
	Rook() :Piece() {}
	Rook(const String name, const int player) :Piece(name, player) {}
};
