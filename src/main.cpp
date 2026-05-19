#include "Board.hpp"

int main() {
	try {
		Board chess = Board("r3k2r/pp2np2/2pB2pp/3p1p2/3P4/3n2PB/PPP1PP1P/R3K2R b KQkq - 0 1", FEN);
		chess.updateLegalMoves();
		std::cout << chess << "\n";
	} catch (std::exception &e) {
		std::cout << e.what() << "\n";
	}

}