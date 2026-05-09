/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 16:06:23 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/05/06 21:53:03 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Board.hpp"

Board::Board(): letters("_pkqrbnp") {
	this->fromFen(START_POSITION);
}

Board::~Board() {}

Board::Board(const Board& other): letters("_pkqrbnp") {
	*this = other;
}

Board::Board(const std::string& s, int type): letters("_pkqrbnp") {
	switch (type) {
		case ALG: {
			this->fromAlg(s);
			break;
		}
		case FEN: {
			this->fromFen(s);
			break;
		}
		default: {throw (UnknownStringRepresentationError());}
	};
}

Board& Board::operator=(const Board& other) {
	this->bkc = other.bkc;
	this->bqc = other.bqc;
	this->wkc = other.wkc;
	this->wqc = other.wqc;
	this->moveRule = other.moveRule;
	this->fullMoves = other.fullMoves;
	this->cur = other.cur;
	this->drawTracker = other.drawTracker;
	this->status = other.status;

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			this->board[i][j] = other.board[i][j];
		}
	}

	return (*this);
}

coords getCoords(int rank, int file) {
	coords p;

	p.rank = rank;
	p.file = file;
	return p;
}

pos Board::makePos() const {
	pos p;

	p.r1 = 0;
	for (int i = 0; i < 8; i++) {
		p.r1 += abs(this->board[0][i].getType()) + ((this->board[0][i].getCol() == BLACK) << 4);
		p.r1 <<= 8;
	}

	p.r2 = 0;
	for (int i = 0; i < 8; i++) {
		p.r2 += abs(this->board[1][i].getType()) + ((this->board[1][i].getCol() == BLACK) << 4);
		p.r2 <<= 8;
	}

	p.r3 = 0;
	for (int i = 0; i < 8; i++) {
		p.r3 += abs(this->board[2][i].getType()) + ((this->board[2][i].getCol() == BLACK) << 4);
		p.r3 <<= 8;
	}

	p.r4 = 0;
	for (int i = 0; i < 8; i++) {
		p.r4 += abs(this->board[3][i].getType()) + ((this->board[3][i].getCol() == BLACK) << 4);
		p.r4 <<= 8;
	}

	p.r5 = 0;
	for (int i = 0; i < 8; i++) {
		p.r5 += abs(this->board[4][i].getType()) + ((this->board[4][i].getCol() == BLACK) << 4);
		p.r5 <<= 8;
	}


	p.r6 = 0;
	for (int i = 0; i < 8; i++) {
		p.r6 += abs(this->board[5][i].getType()) + ((this->board[5][i].getCol() == BLACK) << 4);
		p.r6 <<= 8;
	}

	p.r7 = 0;
	for (int i = 0; i < 8; i++) {
		p.r7 += abs(this->board[6][i].getType()) + ((this->board[6][i].getCol() == BLACK) << 4);
		p.r7 <<= 8;
	}

	p.r8 = 0;
	for (int i = 0; i < 8; i++) {
		p.r8 += abs(this->board[7][i].getType()) + ((this->board[7][i].getCol() == BLACK) << 4);
		p.r8 <<= 8;
	}

	return p;
}

Board::AlgError::AlgError(const char* msg): msg(msg) {}
Board::FenError::FenError(const char* msg): msg(msg) {}
Board::UnknownStringRepresentationError::UnknownStringRepresentationError() {}

const char* Board::AlgError::what() const throw() {return this->msg;}
const char* Board::FenError::what() const throw() {return this->msg;}
const char* Board::UnknownStringRepresentationError::what() const throw() {return "Unknown game string representation type";}

bool Board::isCheck(int col) {
	/* coords king = this->Pieces[KING * col][0];
	Piece& cur = this->board[0][0];

	for (int i = 1; i < 1 + KNIGHT; i++) {
		for (coords c: this->Pieces[-i * col]) {
			cur = this->board[c.rank][c.file];
			if (std::find(cur.legalCaptures.begin(), cur.legalCaptures.end(), king) != cur.legalCaptures.end()) {
				return (true);
			}
		} 
	}
	return (false); */
	(void)col;
	return (false);
} 

int Board::getLegalMoves() {
	int count = 0;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->board[i][j].getCol() == this->turn) {
				count += this->board[i][j].getLegalMoves(*this);
			}
		}
	}
	if (count)
		return (CONTINUE);
	if (this->isCheck(this->turn)) {
		this->status = -this->turn;
		return (-this->turn);
	}
	this->status = DRAW;
	return (DRAW);
}

void Board::makePassable(const coords c) {
	if (this->board[c.rank][c.file].getType() == PAWN) {
		if ((c.rank == 4 && this->board[c.rank][c.file].getCol() == WHITE) || (c.rank == 3 && this->board[c.rank][c.file].getCol() == BLACK))
			throw(FenError("wrong colour pawn to make passable in given rank"));
		this->enPassant = c;
	}
	else {
		throw(FenError("not a pawn in given passable pawn coordinate"));
	}
}

void Board::place(coords from, coords to) {
	if (this->board[from.rank][from.file].getType()) {
		this->board[to.rank][to.file] = this->board[from.rank][from.file];
		this->board[from.rank][from.file] = Piece();
	}
}