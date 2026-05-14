#include "Board.hpp"

int main() {
	try {
		Board chess = Board("1B6/2n5/p1N1P2R/P1K3N1/4Pk2/1Q2p2p/6nP/1B4R1 w - - 0 1", FEN);
		std::cout << chess << "\n" << chess.getfen();
	} catch (std::exception &e) {
		std::cout << e.what();
	}

}