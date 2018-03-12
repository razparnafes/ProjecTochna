/*
 * Parser.h
 *
 *  Created on: 11 Mar 2018
 *      Author: Raz Parnafes
 */

#ifndef PARSER_H_
#define PARSER_H_

#define GAME_MAX_LINE_LENGTH 1024

//a type used to represent a command
typedef enum {
	G_UNDO,
	G_MOVE,
	G_GET_MOVES,
	G_QUIT,
	G_SAVE,
	G_RESET,
	G_INVALID_LINE,
} GAME_COMMAND;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	GAME_COMMAND cmd;
	int arg1;
	int arg2;
	char arg3[GAME_MAX_LINE_LENGTH];
} GameCommand;

/**
 * parses an x,y pair into a square int in our format.
 * @param x,y are the coordinates as input by user
 * @return - square in int form, -1 if out of bounds.
 */
int parseSquare(char x, char y);

/**
 * Parses a specified line.
 * If the line has arguments they appear in arg1, arg2, arg3 in order.
 * Values are undefined for commands that don't use specified arguments.
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   arg1 - integer argument (used in MOVE (from), GET_MOVES)
 *	 arg2 - integer argument (used in MOVE (to))
 *	 arg3 - string* (used in SAVE)
 */
GameCommand gameParseLine(const char* str);

#endif /* PARSER_H_ */
