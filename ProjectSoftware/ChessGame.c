
#include "ChessGame.h"


ChessPiece* getSquare(int index, ChessGame* game){
	//Assumes 0=<r,c<8
	int r = index/10;
	int c = index%10;
	return game->board[r][c];
}

void setSquare(int index, ChessPiece* p, ChessGame* game){
	//Assumes 0=<r,c<8
	int r = index/10;
	int c = index%10;
	game->board[r][c] = p;
}

int packSquare(int* square){
	return square[0]*10+square[1];
}

void unpackSquare(int index, int upSquare[]){
	upSquare[0] = index/10;
	upSquare[1] = index%10;
}

ChessPiece* createChessPiece(PieceType type, int color, int square){
	//create struct
	ChessPiece* p = (ChessPiece*) calloc(1, sizeof(ChessPiece));
	if (p == NULL){
		//ToDo: error
		return p;
	}

	//init values
	p->color = color;
	p->type = type;
	p->square = square;
	p->alive = true;

	//init name (as lowercase, convert to uppercase at end)
	switch(type){
	  case PAWN:
		  p->name = 'p';
		  break;
	  case BISHOP:
		  p->name = 'b';
		  break;
	  case ROOK:
		  p->name = 'r';
		  break;
	  case KNIGHT:
		  p->name = 'n';
		  break;
	  case KING:
		  p->name = 'k';
		  break;
	  case QUEEN:
		  p->name = 'q';
		  break;
	}
	if (color == BLACK){			//converts to uppercase if needed
		p->name = toupper(p->name);
	}

	return p;
}

ChessGame* createChessGame(int historySize){
	//check historySize
	if (historySize < 0){
		return NULL;
	}

	//init ChessGame struct
	ChessGame* new_game = (ChessGame*) calloc(1, sizeof(ChessGame));
	if (new_game == NULL){
		//ToDo: error
	}

	//zero all arrays, set initial values, init history list
	memset(&new_game->board, 0, sizeof(new_game->board));
	memset(&new_game->white_p, 0, sizeof(new_game->white_p));
	memset(&new_game->black_p, 0, sizeof(new_game->black_p));
	new_game->cur_player = WHITE;
	new_game->check = false;
	new_game->history = spArrayListCreate(historySize*6);
	if (new_game->history == NULL){
		//ToDo: error
	}

	return new_game;
}

void destroyChessGame(ChessGame* src){
	//destroy chesspieces
	ChessPiece** list = src->white_p;
	for (int i=0; i<2; i++){
		for (int j=0; j<2*BOARD_SIZE; j++){
			free(list[j]);
		}
		list = src->black_p;
	}

	//destroy rest
	spArrayListDestroy(src->history);
	free(src);
}

ChessPiece* copyChessPiece(ChessPiece* src){
	//create new chess piece
	ChessPiece* new_piece = (ChessPiece*) calloc(1, sizeof(ChessPiece));
	if (new_piece == NULL){
		//ToDo: error
		return NULL;
	}

	//copy values
	new_piece->color = src->color;
	new_piece->square = src->square;
	new_piece->type = src->type;
	new_piece->name = src->name;
	new_piece->alive = src->alive;

	return new_piece;
}

CGMessage setPiecesFromList(ChessPiece* white[16], ChessPiece* black[16], ChessGame* game){
	ChessPiece** list = white;
	for (int i=0; i<2; i++){					//for each of the lists
		for (int j=0; j<16; j++){		//for each index in the list
			if (list[j]->alive){				//(if not empty)
				//create chess piece
				ChessPiece* p = copyChessPiece(list[j]);
				if (p == NULL){
					//ToDo:error
					return CG_FAIL;
				}

				//update on board and add to list in game
				int sup[2] = {0};
				unpackSquare(p->square, sup);
				game->board[sup[0]][sup[1]] = p;
				if (i == 0){
					game->white_p[j] = p;
				}
				else {game->black_p[j] = p;}
			}
		}
		list = black;
	}
	return CG_SUCCESS;
}

ChessGame* copyChessGame(ChessGame* src){
	//create empty game
	ChessGame* copy = createChessGame(src->history->maxSize);
	if (copy == NULL){
		//ToDo: error
	}
	//copy values
	copy->cur_player = src->cur_player;
	copy->check = src->check;
	copy->history = spArrayListCopy(src->history);
	setPiecesFromList(src->white_p, src->black_p, copy);	//copies all pieces

	return copy;
}

void printBoard(ChessGame* src){
	//makes and prints board line by line
	for (int i=8; i>0; i--){
		//create line and add prefix
		char line[21];
		line[0] = '0' + i;		//line number
		line[1] = '|';
		line[2] = ' ';
		//fill line of board
		ChessPiece* p;
		for (int j=0; j<8; j++){
			p = src->board[i-1][j];
			int index = 2*j+3;
			line[index] = (p == NULL) ? '_' : p->name;
			line[index+1] = ' ';
		}
		//create line suffix and print
		line[18] = ' ';
		line[19] = '|';
		line[20] = 0;
		printf("%s\n", &line);
	}
	//print last lines
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");
}


void doMove(int from, int to, ChessGame* game){
	//deal with captures
	ChessPiece* c = getSquare(to, game);
	if (c != NULL){					//if move is a capture...
		c->alive = false;
	}

	//move piece in from to to (board and piece)
	ChessPiece* p = getSquare(from, game);
	setSquare(from, NULL, game);
	setSquare(to, p, game);
	p->square = to;

	//update player
	game->cur_player = game->cur_player^1;

	//push to history
	spArrayListAddFirst(game->history, (int) c);
	spArrayListAddFirst(game->history, from);
	spArrayListAddFirst(game->history, to);
}

CGMessage undoMove(ChessGame* game){
	//check if history exists
	if (spArrayListIsEmpty(game->history)){
		return CG_EMPTY;
	}

	//pops to, from, captured piece from history
	int to = spArrayListGetFirst(game->history);
	spArrayListRemoveFirst(game->history);
	int from = spArrayListGetFirst(game->history);
	spArrayListRemoveFirst(game->history);
	ChessPiece* c = (ChessPiece*) spArrayListGetFirst(game->history);
	spArrayListRemoveFirst(game->history);

	//moves piece from to to from, updates player
	ChessPiece* p = getSquare(to, game);
	setSquare(from, p, game);
	p->square = from;
	game->cur_player = game->cur_player^1;

	//revives captures player
	setSquare(to, c, game);
	if (c != NULL){
		c->alive = true;
		c->square = to;
	}

	return CG_SUCCESS;
}









