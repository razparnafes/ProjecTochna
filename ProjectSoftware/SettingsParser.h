#ifndef SPFIARPARSER_H_
#define SPFIARPARSER_H_
#include <stdbool.h>

//specify the maximum line length
#define SP_MAX_LINE_LENGTH 2048

//a type used to represent a command
typedef enum {
	SP_GAME_MODE,
	SP_DIFFICULTY,
	SP_USER_COLOR,
	SP_LOAD,
	SP_DEFAULT,
	SP_PRINT_SETTINGS,
	SP_QUIT,
	SP_START,
	SP_INVALID_LINE,
} SP_COMMAND;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	SP_COMMAND cmd;
	int narg;
	char sarg[SP_MAX_LINE_LENGTH];
} SPCommand;

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool SettingsParserIsInt(const char* str);

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
SPCommand SettingsParserPraseLine(const char* str);

#endif
