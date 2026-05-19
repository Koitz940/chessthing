#include "Board.hpp"

int main() {
	try {
		Board chess = Board("k7/8/1QK5/8/8/8/8/8 b - - 0 1", FEN);
		chess.updateLegalMoves();
		std::cout << chess << "\n";
	} catch (std::exception &e) {
		std::cout << e.what();
	}

}