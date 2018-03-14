#include "MiniMaxAux.h"

int MiniMaxAuxNodeVal(ChessGame* currentGame, int depth, int max, int bestYet){
	int nodeVal = (max == 1) ? -1000 : 1000;
	int tempVal = 0;
	int check = 0;
	if(depth = 0){
		return MiniMaxAuxScoreBoard(currentGame);
	}
	if(isCheckMate(currentGame)){
		return nodeVal;
	}
	ChessPiece** lst = (currentGame->cur_player == WHITE) ? currentGame->white_p : currentGame->black_p;
	SPArrayList* moves;
	ChessPiece* piece;
	for(int i=0; i<16; i++){
		piece = lst[i];
		if(!piece->alive){
			continue;
		}
		moves = getMoves(piece->square, currentGame);
		for(int j=0; j<moves->actualSize; j++){
			doMove(currentGame, piece->square, moves->elements[j].val);
			tempVal = MiniMaxAuxNodeVal(currentGame, depth-1, 1-max, nodeVal);
			nodeVal = (max == 1) ? MAX(nodeVal, tempVal) : MIN(nodeVal, tempVal);
			undoMove(currentGame);
			if((max == 1) ? (nodeVal >= bestYet) : (nodeVal <= bestYet)){
				spArrayListDestroy(moves);
				return nodeVal;
			}
			check |= 1;
		}
		spArrayListDestroy(moves);
	}
	if(check == 0){
		return 0;
	}
	return nodeVal;
}


int MiniMaxAuxScoreBoard(ChessGame* currentGame){
	int score=0;
	int player = (currentGame->cur_player == WHITE) ? 1 : -1;
	score += player * MiniMaxAuxScorePieces(currentGame->white_p);
	score -= player * MiniMaxAuxScorePieces(currentGame->black_p);
	return score;
}


int MiniMaxAuxScorePieces(ChessPiece** lst){
	int score=0;
	ChessPiece* piece;
	for(int i=0; i<16; i++){
		piece = lst[i];
		if(piece->alive){
			switch(piece->type){
			    case PAWN: score += 1; break;
			    case BISHOP: score += 3; break;
			    case ROOK: score += 5; break;
			    case KNIGHT: score += 3; break;
			    case KING: score += 100; break;
			    case QUEEN: score += 9; break;
			}
		}
	}
	return score;
}


int MiniMaxAuxOrderMoves(int* move1, int* move2){
	for(int i=0; i<MINIMAXAUX_MOVE_LENGTH; i++){
		if(move1[i] != move2[i]){
			return move1[i]-move2[i];
		}
	}
	return 0;
}
