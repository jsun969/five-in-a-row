#pragma once

#include "GamePlay.hpp"
#include <unordered_map>

using PieceToChar = std::unordered_map<Piece, std::string>;

class IO {
protected:
	GamePlay& game;
	const PieceToChar& pieceChar;

public:
	IO(GamePlay& game, const PieceToChar& pieceChar) : game(game), pieceChar(pieceChar) {
	}
	virtual ~IO() = default;
	virtual std::pair<int, int> input(Piece currentPiece) const = 0;
	virtual void output() const = 0;
};