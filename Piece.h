#pragma once
#include "String.h"

class Piece {
private:
	String name;
	int player;
public:
	Piece();
	Piece(const String name, const int player);
	void setName(const String name);
	void setPlayer(const int player);
	String getName() const; 
	int getPlayer() const;
};
