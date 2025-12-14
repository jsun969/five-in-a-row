#pragma once

#include "IO.hpp"

class TextIO : public IO {
public:
	using IO::IO;
	std::pair<int, int> input(Piece currentPiece) const override;
	void output() const override;
};