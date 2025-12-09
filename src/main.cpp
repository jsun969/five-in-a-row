#include <array>
#include <iomanip>
#include <iostream>
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

class Game {
private:
	std::array<std::array<Piece, SIZE>, SIZE> board;

public:
	Game() {
		for (auto& row : board) {
			row.fill(Piece::Empty);
		}
	};
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
	bool placePiece(int x, int y, Piece piece) {
		int row = SIZE - y;
		int col = x - 1;
		if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[row][col] != Piece::Empty) {
			return false;
		}
		board[row][col] = piece;
		return true;
	}
	void gameLoop() {
		bool firstMove = true;
		printBoard();
		int x, y;
		while (true) {
			do {
				std::cout << (firstMove ? "Black" : "White") << "'s turn. Enter x y: ";
				std::cin >> x >> y;
			} while (!placePiece(x, y, firstMove ? Piece::Black : Piece::White));
			firstMove = false;
			printBoard();
		}
	}
};

int main() {
	Game game;
	game.gameLoop();
	return 0;
}