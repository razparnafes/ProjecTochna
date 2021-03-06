/*
 * GameRules.h
 *
 *  This module contains aux functions for the main game module
 *  Most functions pertaining to chess appear here (as opposed to general game functions)
 *  This module includes:
 *  	- initGamePieces - sets up pieces for game start
 *  	- isLegalMove - checks if a certain move is legal
 *  	- getLegalMoves - returns all legal moves from a specific square
 *  	- isThreatened - checks if specific square is threatened
 *  	- isCapture - checks if move is a capture
 *  	- isCheck - checks if king is threatened
 *  	- isCheckMate
 */

#ifndef GAMERULES_H_
#define GAMERULES_H_

#include "ChessGame.h"

typedef enum game_rules_message_t {
	GR_SUCCESS,
	GR_FAIL,
	GR_INVALID_INPUT,
	GR_EMPTY_SQUARE,
	GR_ILLEGAL_MOVE,
	GR_STILL_CHECK,
	GR_MAKES_CHECK,
} GRMessage;


//----------------------------------------


/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);
/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);
/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);
/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);
/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);
/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);
/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);

/**
 * initiates the start of a chess game on a given empty game
 * white are always down
 * @param game - the game to initiate on
 * @return - GR_FAIL or GR_SUCCESS (fail is a calloc fail in copy chess piece)
 */
GRMessage initGamePieces(ChessGame* game);



/**
 * finds all legal moves from a specific square
 * doesn't change game board, but may corrupt undo-moves list
 * @param square - square from which move starts
 * @param game - the current game
 * @return
 * a pointer to an array list containing all legal moves from the given square
 * NULL for no moves or illegal input
 */
SPArrayList* getMoves(int square, ChessGame* game);

/**
 * checks if given square is threatened by the opponents pieces
 * @param square - the square to check. May be empty, but assumes valid
 * @param game - the current game
 * @return true iff square is threatened
 */
bool isThreatened(int square, ChessGame* game);

/*
 * checks if given move is legal (in all regards)
 * doesn't change game board, but may corrupt undo-moves list
 * @param to, from - the start and end of the move
 * @param game - the current game
 * @return
 * GR_INVALID_INPUT if move is invalid
 * GR_EMPTY_SQUARE if from square is empty
 * GR_ILLEGAL_MOVE if illegal move
 * GR_STILL_CHECK if king was threatened and is still
 * GR_MAKES_CHECK if king becomes threatened
 * GR_SUCCESS otherwise
 */
GRMessage isLegalMove(int from, int to, ChessGame* game);

//Todo: isCheck ??

#endif /* GAMERULES_H_ */
