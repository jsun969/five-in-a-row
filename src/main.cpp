#include "GamePlay.hpp"
#include "TextIO.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>

const std::unordered_map<Piece, std::string> PIECE_TO_CHAR = {
	{ Piece::Empty, "+" },
	{ Piece::White, "W" },
	{ Piece::Black, "B" }
};

class Game {
private:
	GamePlay gamePlay;
	std::unique_ptr<IO> textIO;

public:
	Game() : gamePlay(15), textIO(std::make_unique<TextIO>(gamePlay, PIECE_TO_CHAR)) {
	}
	void start() {
		bool firstPlayerTurn = true;
		while (true) {
			textIO->output();
			Piece currentPiece = firstPlayerTurn ? Piece::Black : Piece::White;
			auto [x, y] = textIO->input(currentPiece);
			if (gamePlay.checkWin(x, y, currentPiece)) {
				textIO->output();
				std::cout << (currentPiece == Piece::Black ? "Black" : "White") << " wins!\n";
				break;
			}
			firstPlayerTurn = !firstPlayerTurn;
		}
	}
};

int main() {
	Game game;
	game.start();
	return 0;
}