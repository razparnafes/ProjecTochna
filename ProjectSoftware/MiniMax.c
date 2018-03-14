#include "MiniMax.h"

int* MinimaxSuggestMove(ChessGame* currentGame, int maxDepth){
	int nodeVal = -1000, tempVal, tempMove[MINIMAXAUX_MOVE_LENGTH];
	int* bestMove;
	ChessPiece** lst;
	SPArrayList* moves;
	ChessPiece* piece;
	ChessGame* tempGame;
	if(currentGame == NULL || (maxDepth <= 0) || IsGameOver(currentGame)){
		return NULL;
	}
	tempGame = copyChessGame(ChessGame* currentGame);
	if(tempGame == NULL){
		return NULL;
	}
	bestMove = (int*) calloc(MINIMAXAUX_MOVE_LENGTH, sizeof(int));
	if(bestMove == NULL){
		destroy(ChessGame(tempGame))
		return NULL;
	}
	lst = (tempGame->cur_player == WHITE) ? tempGame->white_p : tempGame->black_p;
	for(int i=0; i<16; i++){
		piece = lst[i];
		if(!piece->alive){
			continue;
		}
		moves = getMoves(piece->square, tempGame);
		tempMove[0] = piece->square;
		for(int j=0; j<(moves->actualSize); j++){
			doMove(tempGame, piece->square, moves->elements[j].val);
			tempVal = MiniMaxAuxNodeVal(tempGame, maxDepth-1, 0, nodeVal);
			if(nodeVal <= tempVal){
				tempMove[1] = moves->elements[j].val;
				if((tempVal != nodeVal) || (MiniMaxAuxOrderMoves(tempMove, bestMove) < 0)){
					nodeVal = tempVal;
					for(int i=0; i<MINIMAXAUX_MOVE_LENGTH; i++){
						bestMove[i] = tempMove[i];
					}
				}
			}
			undoMove(tempGame);
		}
		spArrayListDestroy(moves);
	}
	destroy(ChessGame(tempGame))
	return bestMove;
}
