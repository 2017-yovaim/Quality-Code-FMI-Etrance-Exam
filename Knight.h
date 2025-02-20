#pragma once
#include "Piece.h"

class Knight :public Piece {
public:
	Knight() :Piece() {}
	Knight(const String name,  const int player) :Piece(name, player) {}
};