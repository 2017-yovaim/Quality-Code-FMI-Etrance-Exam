#pragma once
#include "Piece.h"


class Queen : public Piece {
public:
	Queen() :Piece() {}
	Queen(const String name, const int player) :Piece(name, player) {}
};