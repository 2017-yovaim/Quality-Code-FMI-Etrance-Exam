#pragma once
#include "Piece.h"

class King :public Piece {
public:
	King() :Piece() {}
	King(const String name, const int player) :Piece(name,  player) {}
};