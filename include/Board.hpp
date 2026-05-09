/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:39:18 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/05/06 21:51:22 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"

class Board {
	protected:
		bool wkc; //these 4 are a flag for each sides castling rights, could make a single char storing each of these in one
		bool wqc;
		bool bkc;
		bool bqc;
		int turn;
		int moveRule; //if 100 half moves have been made without a pawn being pushed or a piece being taken, the game ends in a draw
		int fullMoves;
		std::map<pos, int> drawTracker; //will keep track of positions that happened, positions will be hashed as 8 size_ts wrapped in struct position
		std::vector<Piece*> cur;
		int status;
		coords	enPassant;

		void fromFen(const std::string& fen);
		void fromAlg(const std::string& alg);
		pos makePos() const;
		void castlingfRightsHandler(const std::string& rights);
		void makePassable(const coords);

	public:
		Board();
		~Board();
		Board(const Board& other);
		Board(const std::string& s, int type);
		
		Board& operator=(const Board& other);

		std::string getfen() const;

		std::vector<std::vector<int>> getBoard() const;
		Piece board[8][8];
		bool getwkc() const;
		bool getwqc() const;
		bool getbkc() const;
		bool getbqc() const;
		int getTurn() const;
		int getMoveRule() const;
		int getFullMoves() const;
		bool isValidFENchar(int c) const;
		int	charToInt(int c) const;
		bool isCheck(int col);
		int getLegalMoves();
		void place(coords from, coords to);
		coords getEnPassant() const;
		void setEnPassant(coords c);

		const char letters[9];

		class FenError: public std::exception {
			const char* msg;
			public:
				const char* what() const throw();
				FenError(const char* msg);
		};

		class AlgError: public std::exception {
			const char* msg;
			public:
				const char* what() const throw();
				AlgError(const char* msg);
		};

		class UnknownStringRepresentationError: public std::exception {
			public:
				const char* what() const throw();
				UnknownStringRepresentationError();
		};
};

coords getCoords(int rank, int file);
std::ostream& operator<<(std::ostream& os, const Board& chess);
std::ostream& operator<<(std::ostream& os, const coords& coord);

bool operator==(const coords& a, const coords& b);

#endif