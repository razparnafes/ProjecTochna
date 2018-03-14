#include "SettingsParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



bool spParserIsInt(const char* str){
	bool isInt = true;
	int start = 0;
	// check that this is an non empty string
	if(str == NULL || strlen(str)<=0){
		return false;
	}
	// check if the first char is '-'
	if(str[0] == '-'){
		start = 1;
		if(strlen(str)==1){
			// then str=="-" return false
			return false;
		}
	}
	// check that each char is a digit
	for(int i=start; str[i] != 0; i++){
		isInt = isInt && ((str[i] <= '9') && (str[i] >= '0'));
	}
	return isInt;
}


SPCommand spParserPraseLine(const char* str){
	const char del[7] = " \t\r\n";
	char copystr[SP_MAX_LINE_LENGTH] = {0};
	strcpy(copystr, str);

	SPCommand command;
	char *command_type, *arg;
	command.cmd = SP_INVALID_LINE;
	command.narg = -1;

	// check according to string whether this is a valid command (including argument)
	command_type = strtok(copystr, del);
	if(command_type != NULL){
		arg = strtok(NULL, del);
		if(!strcmp(command_type, "game_mode") && spParserIsInt(arg)){
			// set game mode
			command.cmd = SP_GAME_MODE;
			command.narg = atoi(arg);
		}
		if(!strcmp(command_type, "difficulty") && spParserIsInt(arg)){
			// set difficulty
			command.cmd = SP_DIFFICULTY;
			command.narg = atoi(arg);
		}
		if(!strcmp(command_type, "user_color") && spParserIsInt(arg)){
			// set user color
			command.cmd = SP_USER_COLOR;
			command.narg = atoi(arg);
		}
		if(!strcmp(command_type, "load")){
			// load settings
			command.cmd = SP_LOAD;
			strcpy(command.sarg, arg);
		}
		if(!strcmp(command_type, "default")){
			// default settings
			command.cmd = SP_DEFAULT;
		}
		if(!strcmp(command_type, "print_settings")){
			// print settings
			command.cmd = SP_PRINT_SETTINGS;
		}
		if(!strcmp(command_type, "quit")){
			// quit
			command.cmd = SP_QUIT;
		}
		if(!strcmp(command_type, "start")){
			// start game
			command.cmd = SP_START;
		}
	}
	return command;
}
