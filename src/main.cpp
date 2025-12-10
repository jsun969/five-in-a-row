#include <array>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <unordered_map>

constexpr int SIZE = 15; // Must be less than 100

enum class Piece {
	Empty,
	White,
	Black
};

const std::unordered_map<Piece, char> PIECE_TO_CHAR = {
	{ Piece::Empty, '.' },
	{ Piece::White, 'W' },
	{ Piece::Black, 'B' }
};

const std::array<std::pair<int, int>, 4> DIRECTIONS = { {
		{ 0, 1 }, // Horizontal
		{ 1, 0 }, // Vertical
		{ 1, 1 }, // Diagonal top-left to bottom-right
		{ 1, -1 } // Diagonal top-right to bottom-left
} };

class Game {
private:
	std::array<std::array<Piece, SIZE>, SIZE> board;

	void printBoard() const {
		std::cout << "\033[2J\033[1;1H"; // Clear terminal
		for (int i = 0; i < SIZE; ++i) {
			std::cout << std::setw(2) << SIZE - i << ' ';
			for (int j = 0; j < SIZE; ++j) {
				auto ch = PIECE_TO_CHAR.at(board[i][j]);
				std::cout << ch << ' ';
			}
			std::cout << '\n';
		}
		std::cout << "   ";
		for (int i = 1; i <= SIZE; ++i) {
			std::cout << (i >= 10 ? i / 10 : i) << ' ';
		}
		std::cout << "\n   ";
		for (int i = 1; i <= SIZE; ++i) {
			if (i < 10) {
				std::cout << "  ";
			} else {
				std::cout << i % 10 << ' ';
			}
		}
		std::cout << '\n';
	}

	std::tuple<int, int> xyToRowCol(int x, int y) const {
		int row = SIZE - y;
		int col = x - 1;
		return std::make_tuple(row, col);
	}

	bool checkRowColInBounds(int row, int col) const {
		return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
	}

	bool placePiece(int x, int y, Piece piece) {
		auto [row, col] = xyToRowCol(x, y);
		if (!checkRowColInBounds(row, col) || board[row][col] != Piece::Empty) {
			return false;
		}
		board[row][col] = piece;
		return true;
	}

	bool checkWin(int x, int y, Piece player) const {
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

public:
	Game() {
		for (auto& row : board) {
			row.fill(Piece::Empty);
		}
	};

	void gameLoop() {
		bool firstMove = true;
		printBoard();
		int x = -1, y = -1;
		while (true) {
			bool lastPlayerWin = checkWin(x, y, firstMove ? Piece::White : Piece::Black);
			if (lastPlayerWin) {
				std::cout << (firstMove ? "White" : "Black") << " wins!\n";
				break;
			}
			do {
				std::cout << (firstMove ? "Black" : "White") << "'s turn. Enter x y: ";
				std::cin >> x >> y;
			} while (!placePiece(x, y, firstMove ? Piece::Black : Piece::White));
			firstMove = !firstMove;
			printBoard();
		}
	}
};

int main() {
	Game game;
	game.gameLoop();
	return 0;
}