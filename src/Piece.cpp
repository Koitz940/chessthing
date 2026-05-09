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

Piece::Piece(): type(0), col(0), moves{
	&Piece::getLegalNoneMoves,
    &Piece::getLegalPawnMoves,
	&Piece::getLegalKingMoves,
	&Piece::getLegalQueenMoves,
	&Piece::getLegalRookMoves,
    &Piece::getLegalBishopMoves,
    &Piece::getLegalKnightMoves,
} {
	this->legalMoves = std::vector<coords>();
	this->legalCaptures = std::vector<coords>();
}

Piece::~Piece() {}

Piece::Piece(const Piece& other): moves{
	&Piece::getLegalNoneMoves,
    &Piece::getLegalPawnMoves,
	&Piece::getLegalKingMoves,
	&Piece::getLegalQueenMoves,
	&Piece::getLegalRookMoves,
    &Piece::getLegalBishopMoves,
    &Piece::getLegalKnightMoves,
} {
	*this = other;
}

Piece::Piece(int type, int col, int rank, int file): type(type), col(col), rank(rank), file(file), moves{
	&Piece::getLegalNoneMoves,
    &Piece::getLegalPawnMoves,
	&Piece::getLegalKingMoves,
	&Piece::getLegalQueenMoves,
	&Piece::getLegalRookMoves,
    &Piece::getLegalBishopMoves,
    &Piece::getLegalKnightMoves,
} {
	this->legalMoves = std::vector<coords>();
	this->legalCaptures = std::vector<coords>();
}

Piece::Piece(int piece, int rank, int file): type(abs(piece)), col(piece < 0? -1: 1), rank(rank), file(file), moves{
	&Piece::getLegalNoneMoves,
    &Piece::getLegalPawnMoves,
	&Piece::getLegalKingMoves,
	&Piece::getLegalQueenMoves,
	&Piece::getLegalRookMoves,
    &Piece::getLegalBishopMoves,
    &Piece::getLegalKnightMoves,
} {
	this->legalMoves = std::vector<coords>();
	this->legalCaptures = std::vector<coords>();
}

Piece& Piece::operator=(const Piece& other) {
	this->col = other.col;
	this->type = other.type;
	this->legalMoves = std::vector<coords>();
	this->legalCaptures = std::vector<coords>();
	return (*this);
}

int	Piece::getLegalNoneMoves(Board& board) {
	(void)board;
	return (0);
}

int	Piece::getLegalPawnMoves(Board& board) {
	//int count = 0;
	//Board& copy = board;
	(void)board;
	
	//if (copy.board[this->rank][this->file] !=)
	return (1);
}

int	Piece::getLegalBishopMoves(Board& board) {
	(void)board;
	return (1);
}

int	Piece::getLegalKnightMoves(Board& board) {
	(void)board;
	return (1);
}

int Piece::getLegalRookMoves(Board& board) {
	(void)board;
	return (1);
}

int	Piece::getLegalQueenMoves(Board& board) {
	(void)board;
	return (1);
}

int	Piece::getLegalKingMoves(Board& board) {
	(void)board;
	return (1);
}

int Piece::getLegalMoves(Board& board) {
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
