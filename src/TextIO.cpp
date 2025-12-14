#include "TextIO.hpp"

#include <iomanip>
#include <iostream>
#include <utility>

void TextIO::output() const {
	auto const board = game.getBoard();
	auto const size = game.getSize();
	std::cout << "\033[2J\033[1;1H"; // Clear terminal

	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(2) << size - i << ' ';
		for (int j = 0; j < size; ++j) {
			auto ch = pieceChar.at(board[i][j]);
			std::cout << ch << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "   ";
	for (int i = 1; i <= size; ++i) {
		std::cout << (i >= 10 ? i / 10 : i) << ' ';
	}
	std::cout << "\n   ";
	for (int i = 1; i <= size; ++i) {
		if (i < 10) {
			std::cout << "  ";
		} else {
			std::cout << i % 10 << ' ';
		}
	}
	std::cout << '\n';
}

std::pair<int, int> TextIO::input(Piece currentPiece) const {
	int x = -1, y = -1;
	do {
		std::cout << (currentPiece == Piece::Black ? "Black" : "White") << "'s turn. Enter x y: ";
		std::cin >> x >> y;
	} while (!game.placePiece(x, y, currentPiece));
	return { x, y };
}
