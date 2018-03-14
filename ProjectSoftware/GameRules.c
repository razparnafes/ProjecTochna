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




bool isLegalMovePawn(int from, int to, ChessGame* game){
	int fromup[2];
	int toup[2];
	fromup = unpackSquare(from);
	toup = unpackSquare(to);
	int cm = getSquare(from,game)->color == WHITE ? 1 : -1;	//color modifier (to change directions according to color)
	//checks for legal capture move
	if (getSquare(to, game)!=Null &&
		toup[0] - fromup[0] == 1*cm && (	//moves one row forward
		toup[1] - fromup[1] == -1 ||		//and one column over to either side
		toup[1] - fromup[1] == 1)){			//in other words - makes a diagonal move
		return true;
		}
	//checks for legal starting move
	if ((fromup[0]*cm == 1 || fromup[0]*cm == -6) &&	//if at starting row
		toup[1] == fromup[1] &&						//same column
		toup[0] - fromup[0] == 2*cm){				//2 rows forward
		return true;
	}
	//checks for regular move
	if (toup[1] == fromup[1] &&				//same column
		toup[0] - fromup[0] == 1*cm){		//moves one row forward
		return true;
	}
	return false;
}


bool isLegalMoveBishop(int from, int to, ChessGame* game){
	int fromup[2];
	int toup[2];
	int colsgn, rowsgn;
	fromup = unpackSquare(from);
	toup = unpackSquare(to);
	//checks for regular move
	if (abs(toup[1]-fromup[1]) == abs(toup[0]-fromup[0])){//moves one row forward
		rowsgn = (toup[0]-fromup[0])<0 ? -1 : 1;
		colsgn = (toup[1]-fromup[1])<0 ? -1 : 1;
		for(int i=1; i<abs(toup[0]-fromup[0]); i++){
			if(game->board[fromup[0]+rowsgn*i][fromup[1]+colsgn*i] != Null){return false;}
		}
		return true;
	}
	return false;
}


bool isLegalMoveRook(int from, int to, ChessGame* game){
	int fromup[2];
	int toup[2];
	int sgn;
	fromup = unpackSquare(from);
	toup = unpackSquare(to);

	//checks for collunm move
	if (toup[0] == fromup[0]){
		sgn = (toup[1]-fromup[1])<0 ? -1 : 1;											//calc direction of move
		for(int i=1; i<abs(toup[1]-fromup[1]); i++){									//check that no pieces are in the way
			if(game->board[fromup[0]][fromup[1]+sgn*i] != Null){
				return false;
			}
		}
		return true;
	}

	//check for row move
	if(toup[1] == fromup[1]){
		sgn = (toup[0]-fromup[0])<0 ? -1 : 1;											//calc direction of move
		for(int i=1; i<abs(toup[0]-fromup[0]); i++){									//check that no pieces are in the way
			if(game->board[fromup[0]+sgn*i][fromup[1]] != Null){
				return false;
			}
		}
		return true;
	}
	return false;
}



bool isLegalMoveKnight(int from, int to, ChessGame* game){
	int fromup[2];
	int toup[2];
	fromup = unpackSquare(from);
	toup = unpackSquare(to);

	if((abs(fromup[0]-toup[0]) == 1 && abs(fromup[0]-toup[0]) == 2) ||					//check that this is an L move
			(abs(fromup[0]-toup[0]) == 2 && abs(fromup[0]-toup[0]) == 1)){
		return true;
	}
	return false;
}



bool isLegalMoveKing(int from, int to, ChessGame* game){
	int fromup[2];
	int toup[2];
	fromup = unpackSquare(from);
	toup = unpackSquare(to);

	if((abs(fromup[0]-toup[0]) <= 1) && (abs(fromup[0]-toup[0]) <= 1)){					//check that this is an * move
		return true;
	}
	return false;

}



bool isLegalMoveQueen(int from, int to, ChessGame* game){
	//every legal queen move is either a valid rook move or a valid bishop move, and vice versa
	return (isLegalMoveRook(from, to, game) || isLegalMoveBishop(from, to, game));
}



GRMessage isLegalMove(int from, int to, ChessGame* game){
	int toup[2];
	int fromup[2];
	bool check;
	ChessPiece* piece = getSquare(from, game);
	ChessPiece* myKing = game->cur_player == WHITE ? game->white_p[0] : game->black_p[1];

	fromup = unpackSquare(from);
	toup = unpackSquare(to);
	if(from[0]>=ROWS || from[0]<0 || from[1]>=COLS || from[1]<0 ||
			to[0]>=ROWS || to[0]<0 || to[1]>=COLS || to[1]<0 ||
			piece == Null){
		return GR_INVALID_INPUT;
	}

	if(!(getSquare(to, game)==Null || getSquare(to, game)->color != piece->color)){
		return GR_ILLEGAL_MOVE;
	}

	switch(piece->type){
		case PAWN: check = isLegalMovePawn(from, to, game); break;
		case BISHOP: check = isLegalMoveBishop(from, to, game); break;
		case ROOK: check = isLegalMoveRook(from, to, game); break;
		case KNIGHT: check = isLegalMoveKnight(from, to, game); break;
		case KING: check = isLegalMoveKing(from, to, game); break;
		case QUEEN: check = isLegalMoveQueen(from, to, game); break;
	}
	if(!check){
		return GR_ILLEGAL_MOVE;
	}

	doMove(from, to, game);
	if(isThreatened(myKing->square, game)){
		undoMove(game);
		if(isThreatened(myKing->square, game)){
			return GR_STILL_CHECK;
		}
		else{
			return GR_MAKES_CHECK;
		}
	}
	else{
		undoMove(game);
		return GR_SUCCESS;
	}
}


bool isThreatened(int square, ChessGame* game){
	ChessPiece** enemy = (game->cur_player == BLACK) ? game->black_p : game->white_p;
	for(int i=0; i<16; i++){
		if((enemy[i] != Null) && isLegalMove(enemy[i]->square, square, game)){
			return true;
		}
	}

	return false;
}



bool isCheckMate(ChessGame* game){
	ChessPiece** myPieces = (game->cur_player == BLACK) ? game->black_p : game->white_p;
	ChessPiece* piece;

	if(isThreatened(myPieces[0]->square, game)){
		for(int i=0; i<16; i++){
			piece = lst[i];
			if(!piece->alive){
				continue;
			}
			moves = getMoves(piece->square, tempGame);
			if(moves->actualSize != 0){
				return false;
			}
			spArrayListDestroy(moves);
		}
		return true;
	}
	return false;
}




SPArrayList* getMoves(int square, ChessGame* game){
	SPArrayList* moves = spArrayListCreate(ROWS*4);
	int to;

	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			to = packSquare({i,j});
			if(isLegalMove(square, packSquare(to), game)){
				spArrayListAddLast(moves, to);
			}
		}
	}
	return moves;




//____________________________________________________________________
GRMessage initGamePieces(ChessGame* game){
	ChessPiece* white[16];
	ChessPiece* black[16];

	//royalty
	white[0] = createChessPiece(QUEEN, WHITE, 3);
	white[1] = createChessPiece(KING, WHITE, 4);
	black[0] = createChessPiece(QUEEN, BLACK, 73);
	black[1] = createChessPiece(KING, BLACK, 74);

	//pawns
	for (int i=0; i<BOARD_SIZE; i++){
		white[i+2] = createChessPiece(PAWN, WHITE, 10+i);
		black[i+2] = createChessPiece(PAWN, BLACK, 60+i);
		//ToDo: errors?
	}

	//the rest
	white[10] = createChessPiece(ROOK, WHITE, 0);
	white[11] = createChessPiece(ROOK, WHITE, 7);
	black[10] = createChessPiece(ROOK, BLACK, 70);
	black[11] = createChessPiece(ROOK, BLACK, 77);
	white[12] = createChessPiece(KNIGHT, WHITE, 1);
	white[13] = createChessPiece(KNIGHT, WHITE, 6);
	black[12] = createChessPiece(KNIGHT, BLACK, 71);
	black[13] = createChessPiece(KNIGHT, BLACK, 76);
	white[14] = createChessPiece(BISHOP, WHITE, 2);
	white[15] = createChessPiece(BISHOP, WHITE, 5);
	black[14] = createChessPiece(BISHOP, BLACK, 72);
	black[15] = createChessPiece(BISHOP, BLACK, 75);

	setPiecesFromList(white, black, game);
	//Todo: errors?

	for (int i=1; i<BOARD_SIZE; i++){
		free(white[i]);
		free(black[i]);
	}

	return GR_SUCCESS;
}



