#pragma once
#include "Piece.h"

class Bishop :public Piece {
public:
	Bishop() :Piece() {}
	Bishop(const String name, const int player) :Piece(name, player) {}
};
