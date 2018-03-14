#ifndef MINIMAX_H_
#define MINIMAX_H_
#include "MiniMaxAux.h"


/**
 * Given a game state and a Minimax algorithm depth, this function caclulates the best possible move (using Minimax algorithm
 * up to a specified length given by depth) for the current player. The current game state isn't changed by this function 
 * including the history of previous moves. 
 *
 * @param currentGame - The current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm (the depth of the "virutal" tree calculated), assumed to be non negative
 * @return
 * The function returns the best move (calculated using minimax up to depth maxDepth) in the form of an int* to the desctiption of 
 * the move in this form: (int from_square, int to_square) ***THE USER OF THIS FUNCTION MUST RELEASE THIS MOVE***. returns NULL 
 * if a memory allocation failure occurred, or invalid args.
 */
int* MinimaxSuggestMove(ChessGame* currentGame, int maxDepth);

#endif
