#include "GamePlay.hpp"

const std::array<std::pair<int, int>, 4> DIRECTIONS = { {
		{ 0, 1 }, // Horizontal
		{ 1, 0 }, // Vertical
		{ 1, 1 }, // Diagonal top-left to bottom-right
		{ 1, -1 } // Diagonal top-right to bottom-left
} };

bool GamePlay::checkRowColInBounds(int row, int col) const {
	return row >= 0 && row < size && col >= 0 && col < size;
}
std::tuple<int, int> GamePlay::xyToRowCol(int x, int y) const {
	int row = size - y;
	int col = x - 1;
	return std::make_tuple(row, col);
}

GamePlay::GamePlay(int size) : size(size) {
	board.resize(size, std::vector<Piece>(size, Piece::Empty));
}

bool GamePlay::placePiece(int x, int y, Piece piece) {
	auto [row, col] = xyToRowCol(x, y);
	if (!checkRowColInBounds(row, col) || board[row][col] != Piece::Empty) {
		return false;
	}
	board[row][col] = piece;
	return true;
}

bool GamePlay::checkWin(int x, int y, Piece player) const {
	auto [row, col] = xyToRowCol(x, y);
	for (const auto& [dx, dy] : DIRECTIONS) {
		int count = 1;
		// Check in the (dx, dy) direction
		for (int i = 1; i < 5; ++i) {
			int newRow = row + dx * i, newCol = col + dy * i;
			if (!checkRowColInBounds(newRow, newCol) || board[newRow][newCol] != player) {
				break;
			}
			++count;
		}
		// Check in the (-dx, -dy) direction
		int rdx = -dx, rdy = -dy;
		for (int i = 1; i < 5; ++i) {
			int newRow = row + rdx * i, newCol = col + rdy * i;
			if (!checkRowColInBounds(newRow, newCol) || board[newRow][newCol] != player) {
				break;
			}
			++count;
		}
		if (count >= 5) {
			return true;
		}
	}
	return false;
}

Board GamePlay::getBoard() const {
	return board;
}

int GamePlay::getSize() const {
	return size;
}