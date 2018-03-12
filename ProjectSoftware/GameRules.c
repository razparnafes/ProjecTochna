//
#include "GameRules.h"

////-----------isLegalMove functions--------------
///**
// * the following functions check if a specific move is a legal chess move for each piece.
// * they DO NOT check if a move is legal in the sense that is does not endanger the king.
// * @param from - square where the move starts
// * @param to - square where the move ends
// * @param game - the current game
// *
// * Assumes from contains a chess piece of the relevant type
// *
// * @return
// * bool - true iff the move specified is legal
// */
//
//bool isLegalMovePawn(int from, int to, ChessGame* game);
//bool isLegalMoveBishop(int from, int to, ChessGame* game);
//bool isLegalMoveRook(int from, int to, ChessGame* game);
//bool isLegalMoveKnight(int from, int to, ChessGame* game);
//bool isLegalMoveKing(int from, int to, ChessGame* game);
//bool isLegalMoveQueen(int from, int to, ChessGame* game);
//
//bool isLegalMovePawn(int from, int to, ChessGame* game){
//	int fromup[2];
//	int toup[2];
//	fromup = unpackSquare(from);
//	toup = unpackSquare(to);
//	int cm = getSquare(from,game) == WHITE ? 1 : -1;	//color modifier (to change directions according to color)
//	//checks for legal capture move
//	if (isCapture(from, to, game) &&
//		toup[0] - fromup[0] == 1*cm && (	//moves one row forward
//		toup[1] - fromup[1] == -1 ||		//and one column over to either side
//		toup[1] - fromup[1] == 1)){			//in other words - makes a diagonal move
//		return true;
//		}
//	//checks for legal starting move
//	if ((from[0]*cm == 1 || from[0]*cm == -6) &&	//if at starting row
//		toup[1] == fromup[1] &&						//same column
//		toup[0] - fromup[0] == 2*cm){				//2 rows forward
//		return true;
//	}
//	//checks for regular move
//	if (toup[1] == fromup[1] &&				//same column
//		toup[0] - fromup[0] == 1*cm){		//moves one row forward
//		return true;
//	}
//	return false;
//}
//
////-----------getMoves functions--------------
///**
// * the following functions return an ArrayList of legal moves
// * the functions are type specific
// * @param from - square where the move starts
// * @param to - square where the move ends
// * @param list - pointer to an empty arraylist in which to store moves. Assumes empty.
// * @param game - the current game
// *
// * Assumes from contains a chess piece of the relevant type
// *
// * @return
// * bool - true iff the move specified is legal
// */
//
//GRMessage getMovesPawn(int square, SPArrayList* list, ChessGame* game);
//GRMessage getMovesBishop(int square, SPArrayList* list, ChessGame* game);
//GRMessage getMovesRook(int square, SPArrayList* list, ChessGame* game);
//GRMessage getMovesKnight(int square, SPArrayList* list, ChessGame* game);
//GRMessage getMovesKing(int square, SPArrayList* list, ChessGame* game);
//GRMessage getMovesQueen(int square, SPArrayList* list, ChessGame* game);
//
////-----------------------------------------------
//
//
//
//bool isCapture(int from, int to, ChessGame* game){
//	ChessPiece fromp = getSquare(from);
//	ChessPiece top = getSquare(to);
//	if (top != NULL){
//		if (fromp->color ^ top->color == 1){
//			return true;
//		}
//	}
//	return false;
//}


//____________________________________________________________________




