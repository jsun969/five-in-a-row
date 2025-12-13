#pragma once

#include <vector>

enum class Piece {
	Empty,
	White,
	Black
};

using Board = std::vector<std::vector<Piece>>;

class GamePlay {
private:
	Board board;
	int size;

	bool checkRowColInBounds(int row, int col) const;
	std::tuple<int, int> xyToRowCol(int x, int y) const;

public:
	/** `size` should be 9-99 */
	GamePlay(int size);
	bool placePiece(int x, int y, Piece piece);
	bool checkWin(int x, int y, Piece player) const;
	Board getBoard() const;
};