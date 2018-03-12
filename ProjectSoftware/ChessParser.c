/*
 * Parser.c
 *
 *  Created on: 11 Mar 2018
 *      Author: Raz Parnafes
 */
#include "ChessParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseSquare(char x, char y){
	//check valid square
	if (x < '1' || x > '8' || y < 'A' || y > 'H'){
		return -1;
	}

	//translate chars to numbers
	int row = x - '1';
	int col = y - 'A';
	return 10*row + col;
}

GameCommand gameParseLine(const char* str){
	const char del[7] = " \t\r\n";
	char copystr[GAME_MAX_LINE_LENGTH] = {0};
	strcpy(copystr, str);

	GameCommand command;
	char *command_type, *arg1, *arg2;
	command.cmd = G_INVALID_LINE;

	// check according to string whether this is a valid command (including argument)
	command_type = strtok(copystr, del);
	if(command_type != NULL){
		//move
		if(!strcmp(command_type, "move")){
			arg1 = strtok(NULL, del);
			arg2 = strtok(NULL, del);
			arg2 = strtok(NULL, del);
			//if args are good...
			if (strlen(arg1) == 3 && strlen(arg2) == 3){
				command.cmd = G_MOVE;
				command.arg1 = parseSquare(*arg1, *(arg1 + 2));
				command.arg2 = parseSquare(*arg2, *(arg2 + 2));
			}

		}
		//get_moves
		if(!strcmp(command_type, "get_moves")){
			arg1 = strtok(NULL, del);
			if (strlen(arg1) == 3){
				command.cmd = G_GET_MOVES;
			}
		}
		//save
		if(!strcmp(command_type, "save")){
			arg1 = strtok(NULL, del);
			if (arg1 != NULL){
				command.cmd = G_SAVE;
				strcpy(command.arg3, arg1);
			}
		}
		//undo
		if(!strcmp(command_type, "undo")){
			command.cmd = G_UNDO;
		}
		//reswt
		if(!strcmp(command_type, "reset")){
			command.cmd = G_RESET;
		}
		//quit
		if(!strcmp(command_type, "quit")){
			command.cmd = G_QUIT;
		}
	}
	return command;
}

