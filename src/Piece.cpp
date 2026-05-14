/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piece.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:34:08 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/05/06 21:17:28 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Piece.hpp"
#include "Board.hpp"

static bool onBoard(int rank, int file) {
	return(0 <= rank && 7 >= rank && 0 <= file && 7 >= file);
}

Piece::Piece(): type(0), col(0), moves{
	&Piece::calculateLegalNoneMoves,
    &Piece::calculateLegalPawnMoves,
	&Piece::calculateLegalKingMoves,
	&Piece::calculateLegalQueenMoves,
	&Piece::calculateLegalRookMoves,
    &Piece::calculateLegalBishopMoves,
    &Piece::calculateLegalKnightMoves,
} {
	this->legalMoves = std::vector<move>();
}

Piece::~Piece() {}

Piece::Piece(const Piece& other): moves{
	&Piece::calculateLegalNoneMoves,
    &Piece::calculateLegalPawnMoves,
	&Piece::calculateLegalKingMoves,
	&Piece::calculateLegalQueenMoves,
	&Piece::calculateLegalRookMoves,
    &Piece::calculateLegalBishopMoves,
    &Piece::calculateLegalKnightMoves,
} {
	*this = other;
}

Piece::Piece(int type, int col, int rank, int file): type(type), col(col), rank(rank), file(file), moves{
	&Piece::calculateLegalNoneMoves,
    &Piece::calculateLegalPawnMoves,
	&Piece::calculateLegalKingMoves,
	&Piece::calculateLegalQueenMoves,
	&Piece::calculateLegalRookMoves,
    &Piece::calculateLegalBishopMoves,
    &Piece::calculateLegalKnightMoves,
} {
	this->legalMoves = std::vector<move>();
}

Piece::Piece(int piece, int rank, int file): type(abs(piece)), col(piece < 0? -1: 1), rank(rank), file(file), moves{
	&Piece::calculateLegalNoneMoves,
    &Piece::calculateLegalPawnMoves,
	&Piece::calculateLegalKingMoves,
	&Piece::calculateLegalQueenMoves,
	&Piece::calculateLegalRookMoves,
    &Piece::calculateLegalBishopMoves,
    &Piece::calculateLegalKnightMoves,
} {
	this->legalMoves = std::vector<move>();
}

Piece& Piece::operator=(const Piece& other) {
	this->col = other.col;
	this->type = other.type;
	this->legalMoves = other.legalMoves;
	return (*this);
}

const std::vector<move>& Piece::getLegalMoves() const {
	return (this->legalMoves);
}

int	Piece::calculateLegalNoneMoves(Board& board) {
	(void)board;
	return (0);
}

int	Piece::calculateLegalPawnMoves(Board& board) {
	int count = 0;
	Board copy = board;
	
	if (this->col == WHITE) {
		
	}
	return (1);
}

int	Piece::calculateLegalBishopMoves(Board& board) {
	int count = 0;
	Board copy = board;

	for (int i = 0; onBoard(this->rank + i, this->file + i) && board.board[this->rank + i][this->file + i].col != this->col; i++) {
		copy = board;
		copy.board[this->rank + i][this->file + i] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[this->rank + i][this->file + i].col) {
				this->addMove(this->rank + i, this->file + i, CAPTURE);
				count++;
				break;
			}
			this->addMove(this->rank + i, this->file + i, MOVE);
			count++;
		}
	}
	for (int i = 0; onBoard(this->rank + i, this->file - i) && board.board[this->rank + i][this->file - i].col != this->col; i++) {
		copy = board;
		copy.board[this->rank + i][this->file - i] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[this->rank + i][this->file - i].col) {
				this->addMove(this->rank + i, this->file - i, CAPTURE);
				count++;
				break;
			}
			this->addMove(this->rank + i, this->file - i, MOVE);
			count++;
		}
	}
	for (int i = 0; onBoard(this->rank - i, this->file + i) && board.board[this->rank - i][this->file + i].col != this->col; i++) {
		copy = board;
		copy.board[this->rank - i][this->file + i] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[this->rank - i][this->file + i].col) {
				this->addMove(this->rank - i, this->file + i, CAPTURE);
				count++;
				break;
			}
			this->addMove(this->rank - i, this->file + i, MOVE);
			count++;
		}
	}
	for (int i = 0; onBoard(this->rank - i, this->file - i) && board.board[this->rank - i][this->file - i].col != this->col; i++) {
		copy = board;
		copy.board[this->rank - i][this->file - i] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[this->rank - i][this->file - i].col) {
				this->addMove(this->rank - i, this->file - i, CAPTURE);
				count++;
				break;
			}
			this->addMove(this->rank - i, this->file - i, MOVE);
			count++;
		}
	}
	return (count);
}

int	Piece::calculateLegalKnightMoves(Board& board) {
	int count = 0;
	Board copy;
	int ra[] = {1, 1, -1, -1, 2, -2, 2, -2};
	int fa[] = {2, -2, 2, -2, 1, 1, -1, -1};
	int r;
	int f;

	for (int i = 0; i < 8; i++) {
		r = ra[i] + this->rank;
		f = fa[i] + this->file;
		if (onBoard(r, f)) {
			copy = board;
			copy.board[r][f] = *this;
			copy.board[this->rank][this->file] = Piece();
			if (board.board[r][f].col != this->col && !copy.isCheck(this->col)) {
				if (board.board[r][f].col)
					this->addMove(r, f, CAPTURE);
				else 
					this->addMove(r, f, MOVE);
				count++;
			}
		}
	}

	return (count);
}

int Piece::calculateLegalRookMoves(Board& board) {
	int count = 0;
	Board copy;

	for (int i = this->rank; onBoard(i, this->file) && board.board[i][this->file].col != this->col; i++) {
		copy = board;
		copy.board[i][this->file] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[i][this->file].col) {
				this->addMove(i, this->file, CAPTURE);
				count++;
				break;
			}
			this->addMove(i, this->file, MOVE);
			count++;
		}
	}
	for (int i = this->rank; onBoard(i, this->file) && board.board[i][this->file].col != this->col; i--) {
		copy = board;
		copy.board[i][this->file] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[i][this->file].col) {
				this->addMove(i, this->file, CAPTURE);
				count++;
				break;
			}
			this->addMove(i, this->file, MOVE);
			count++;
		}
	}
	for (int i = this->file; onBoard(this->rank, i) && board.board[this->rank][i].col != this->col; i++) {
		copy = board;
		copy.board[this->rank][i] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[this->rank][i].col) {
				this->addMove(this->rank, i, CAPTURE);
				count++;
				break;
			}
			this->addMove(this->rank, i, MOVE);
			count++;
		}
	}
	for (int i = this->file; onBoard(this->rank, i) && board.board[this->rank][i].col != this->col; i--) {
		copy = board;
		copy.board[this->rank][i] = *this;
		copy.board[this->rank][this->file] = Piece();
		if (!copy.isCheck(this->col)) {
			if (board.board[this->rank][i].col) {
				this->addMove(this->rank, i, CAPTURE);
				count++;
				break;
			}
			this->addMove(this->rank, i, MOVE);
			count++;
		}
	}
	return (count);
}

int	Piece::calculateLegalQueenMoves(Board& board) {
	return (this->calculateLegalBishopMoves(board) + this->calculateLegalRookMoves(board));
}

int	Piece::calculateLegalKingMoves(Board& board) {
	(void)board;
	return (1);
}

int Piece::calculateLegalMoves(Board& board) {
	return (this->*moves[abs(this->type)])(board);
}

bool Piece::isLegal(const coords coord) {
	auto it = std::find(this->legalMoves.begin(), this->legalMoves.end(), coord);
	return (it == this->legalMoves.end());
}

int Piece::getType() const {
	return (this->type);
}

void Piece::setType(int type) {
	this->type = type;
}

int Piece::getCol() const {
	return (this->col);
}

void Piece::setCol(int col) {
	this->col = col;
}

int Piece::getPiece() const {
	return (this->col * this->type);
}

void Piece::setPiece(int piece) {
	this->type = abs(piece);
	this->col = piece ? (piece > 0? WHITE: BLACK): 0;
}

void Piece::addMove(int rank, int file, moveType type) {
	move n;

	n.to = getCoords(rank, file);
	n.t = type;
	this->legalMoves.push_back(n);
}