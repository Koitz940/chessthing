/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piece.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:13:16 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/05/06 21:16:50 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <sstream>
#include <iostream>
#include <algorithm>

#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"
#define FEN 0
#define ALG 1

enum type {
	NONE,
	PAWN,
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
};

enum status {
	BLACK = -1,
	CONTINUE,
	WHITE,
	DRAW
};

typedef enum moveType {
	MOVE,
	CAPTURE,
	Q,
	R,
	B,
	N,
	CASTLE,
} moveType;

typedef struct position {
	size_t r1;
	size_t r2;
	size_t r3;
	size_t r4;
	size_t r5;
	size_t r6;
	size_t r7;
	size_t r8;
}	pos;

typedef struct coordinates {
	int rank;
	int file;
}	coords;

typedef struct move {
	coords to;
	moveType t;
} move;

class Board;

class Piece {
	protected:
		int type;
		int col;
		int rank;
		int file;

		int	calculateLegalNoneMoves(Board& board);
		int	calculateLegalPawnMoves(Board& board);
		int	calculateLegalBishopMoves(Board& board);
		int	calculateLegalKnightMoves(Board& board);
		int calculateLegalRookMoves(Board& board);
		int	calculateLegalQueenMoves(Board& board);
		int	calculateLegalKingMoves(Board& board);

		typedef int (Piece::*MoveFunc)(Board&);
		const MoveFunc moves[8];
		std::vector<move> legalMoves;

		void addMove(int rank, int file, moveType type);
		
	public:
		Piece();
		~Piece();
		Piece(const Piece& other);
		Piece(int type, int col, int rank, int file);
		Piece(int piece, int rank, int file);

		Piece& operator=(const Piece& other);

		int	calculateLegalMoves(Board& board);
		const std::vector<move>& getLegalMoves() const;
		
		bool isLegal(coords coord);

		int getType() const;
		void setType(int type);
		int getCol() const;
		void setCol(int col);
		int getPiece() const;
		void setPiece(int piece);
};

#endif