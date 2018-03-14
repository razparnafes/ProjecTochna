#define MINIMAXAUX_MOVE_LENGTH 2
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


/**
 * Given a game state and a Minimax algorithm depth, this function recursively caclulates the value of current node
 * (using Minimax algorithm up to a specified length given by depth), and returns the value of this node. If the param
 * max is 1, the root will be a max node, and 0 if it is a min node.  The current game state isn't changed by this
 * function including the history of previous moves. The bestYet param is used to prune the tree, (to avoid calculating a
 * subtree which can't affect the father of the root of this subtree), and therefore speed up the function.
 *
 * @param currentGame - The current game state, assumed not to be NULL
 * @param depth - The current depth of the miniMax algorithm (the depth of the subtree created), assumed to be non negative
 * @param max - 1 if the root is a max node, and 0 if it is a min node
 * @param bestYet - the current "best yet" value of the father node of this node, if we realize that the value of this node
 * 					cannot improve on this, we return the current best for this node, instead of continueing to calculate the
 					exact value of this node.
 * @return
 * The function returns the value of the (max/min) "imaginary" node defined by currentGame and max and depth, or if pruning 
 * occured the current valuewhich made us realize that we cannot improve on bestYet.
 */
int MiniMaxAuxNodeVal(ChessGame* currentGame, int depth, int max, int bestYet){


/**
 * Given a game state, this function calculates the current value of the game using the scoring function, by passing over
 * all chess pieces and adding/subracting their values. The current game state doesn't change by this function including 
 * the history of previous moves.
 *
 * @param currentGame - The current game state, assumed not to be NULL and not to be over.
 * @return
 * The function returns a integer representing the value of the curent game, from the scoring function.
 */
int MiniMaxAuxScoreBoard(ChessGame* currentGame);


/**
 * Given a list of chess pieces, this function calculates the value of the list using the scoring function, by passing over
 * all chess pieces and adding their values. 
 *
 * @param lst - A list of pointers to chess pieces 
 * @return
 * The function returns a integer representing the value of list, from the scoring function.
 */
int MiniMaxAuxScorePieces(ChessPiece** lst);


/**
 * Given 2 moves (given in (int from, int to) form), this function compares them lexicographicly, as described in page 10,
 * (in the following order of importance : source column (x), source row (y), destination column, destination row)
 *
 * @param move1 - the first move
 * @param move2 - the second move
 * @return
 * The function returns >0 if first is larger, <0 if second is larger, and 0 if they are identicle. 
 */
int MiniMaxAuxOrderMoves(int* move1, int* move2){
