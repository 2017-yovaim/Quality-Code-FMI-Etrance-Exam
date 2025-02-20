#include "Piece.h"

Piece::Piece()
{
	name = "";
	player = 0;
}

Piece::Piece(const String name,const int player)
{
	this->name = name;
	this->player = player;
}

void Piece::setName(const String name)
{
	this->name = name;
}

void Piece::setPlayer(const int player)
{
	this->player = player;
}

String Piece:: getName() const
{
	return name;
}

int Piece::getPlayer() const
{
	return player;
}
