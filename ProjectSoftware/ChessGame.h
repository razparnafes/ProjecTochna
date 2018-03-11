/*
 * ChessGame.h
 *
 * This module defines the ChessGame, ChessPiece and Move structs and includes basic utilities
 * Functions included:
 * 		- getSquare
 * 		- setSquare
 * 		- packSquare
 * 		- unpackSquare
 * 		- createChessPiece
 * 		- createChessGame
 * 		- destroyChessGame
 * 		- copyChessPiece
 * 		- copyChessGame
 * 		- printBoard
 * 		- setPiecesFromList
 * 		- doMove
 * 		- undoMove
 */

/**
 * Data structures:
 * The game contains a board, and two arrays of playing pieces (one for each color).
 * The king is always first.
 * Each square on the board contains a pointer to the piece on it (or a null pointer).
 * Each piece contains the index of it's place on the board.
 * White always starts at lower indexes
 * Board indexes are of the format r*10+c where r is the row and c the column
 * Moves are always a pair of indexes - two seperate ints (!) "to" and "from"
 * history contains 3 (!) ints for each move in the following order:
 * capture, from, to. from and to are ints. capture is a pointer to a piece captures (or null)
 */

#ifndef CHESSGAME_H_
#define CHESSGAME_H_

#include "SPArrayList.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BOARD_SIZE 8
#define WHITE 0
#define BLACK 1
#define HIST_SIZE 3
#define NUM_PIECES 16;

typedef enum piece_type_t {
	PAWN,
	BISHOP,
	ROOK,
	KNIGHT,
	KING,
	QUEEN,
} PieceType;


typedef struct chess_piece_t {
	int color;
	int square;
	PieceType type;
	char name;
	bool alive;
} ChessPiece;


typedef struct chess_game_t {
	ChessPiece* board[BOARD_SIZE][BOARD_SIZE];
	int cur_player;
	ChessPiece* white_p[16];
	ChessPiece* black_p[16];
	bool check;
	bool checkMate;
	SPArrayList* history;
} ChessGame;


typedef enum chess_game_message_t {
	CG_FAIL,
	CG_SUCCESS,
	CG_EMPTY,
} CGMessage;

//---------------------------------------------------------------------

/**
 * converts int to square on board.
 * @param index - an int of the form r*10+c. Assumes this format holds
 * @param game - the current game
 * @return - a pointer to the chesspiece on that square, (or a null pointer)
 */
ChessPiece* getSquare(int index, ChessGame* game);

/**
 * converts 2-array: (r,c) on board to an int
 * @param square - pointer to a 2-array (int)
 * @return - int of the form r*10+c
 */
int packSquare(int* square);

/**
 * converts int to a 2-array: (r,c) on board
 * @param index - an int of the form r*10+c. Assumes this format holds
 * @param upSquare - pointer to a 2-array in which to store coordinates
 * @return - (r,c) where r is a row and c a column
 */
void unpackSquare(int index, int upSquare[]);

/**
 * inits a chess piece
 * @param type, color - obvious
 * @param square - square in packed format
 * @return - pointer to a new chess piece or null if error
 */
ChessPiece* createChessPiece(PieceType type, int color, int square);

/**
 * initiates an empty chess game
 * the board will be empty, and white will be the current player
 * @param historySize - the number of moves to remember
 * @return - a pointer to the new ChessGame, and null of error occurred.
 */
ChessGame* createChessGame(int historySize);

/**
 * destroys chess game and frees all memory
 * @param src - the game to destroy
 */
void destroyChessGame(ChessGame* src);

/**
 * creates a copy of the chess piece
 * @param - pointer to a chess piece
 * @return - pointer to copied chess piece, or null if failed
 */
ChessPiece* copyChessPiece(ChessPiece* src);

/**
 * sets board according to list of pieces
 * assumes lists are of length 16 each, king is first
 * @param white - list of white pieces to set
 * @param black - list of black pieces to set
 * @param game - empty game to set (assumes empty)
 * @return - CG_FAIL or CG_SUCCESS
 */
CGMessage setPiecesFromList(ChessPiece* white[16], ChessPiece* black[16], ChessGame* game);

/**
 * creates an exact copy of the chess game src
 * @param src - the chess game to be copied
 * @return - a pointer to the new chessgame, and null if error occurred
 */
ChessGame* copyChessGame(ChessGame* src);

/**
 * prints the board with correct format
 * @param src - game who's board will be printed
 */
void printBoard(ChessGame* src);

/**
 * does a move. assumes it's legal.
 * includes moving the pieces, removing a piece if captured, and updating the history and cur player
 * @param from, to - the squares of the move. assumes in range, and from square contains a piece.
 * @param game - the game
 * @return fail or success accordingly
 */
void doMove(int from, int to, ChessGame* game);

/**
 * undo's a move - pops from history list and reverts game to previous state.
 * @param game - the game. assumes history list is good.
 * @return - fail or success, or empty if no moves are in history list
 */
CGMessage undoMove(ChessGame* game);

#endif /* CHESSGAME_H_ */
