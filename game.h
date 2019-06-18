/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Jia Jun Yong
 * Student number: s3688090
 */
#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "player.h"
#include "huntWump.h"

#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_NORTH "north"
#define COMMAND_NORTH_SHORTCUT "n"
#define COMMAND_SOUTH "south"
#define COMMAND_SOUTH_SHORTCUT "s"
#define COMMAND_EAST "east"
#define COMMAND_EAST_SHORTCUT "e"
#define COMMAND_WEST "west"
#define COMMAND_WEST_SHORTCUT "w"
#define COMMAND_SHOOT "shoot"
#define COMMAND_QUIT "quit"

#define MAX_LIMIT 200

#define LOAD_STATE 'a'
#define INIT_STATE 'b'
#define GAME_STATE 'c'

#define BOARD_SELECTION_1 "1"
#define BOARD_SELECTION_2 "2"

#define SAME 0

#define INIT_CMD_LENGTH 9

#define STRING_NULL '\0'
#define STRING_SPACE " "
#define STRING_NEWLINE '\n'
#define STRING_COMMA ","
#define STRING_FIRSTCHAR 0

/**
 * Main menu option 1 - play the game as per the specification.
 *
 * This function makes all the calls to board & player and handles interaction
 * with the user (reading input from the console, error checking, etc...).
 *
 * It should be possible to break this function down into smaller functions -
 * but this is up to you to decide and is entirely your own design. You can
 * place the additional functions in this header file if you want.
 *
 * Note that if you don't break this function up it could become pretty big...
 * and marks are allocated to good coding practices.
 */
void game_PlayGame();
Boolean boardLoadHelper(Board, Boolean *);
char *boardLoadReader(char[], Board);
Boolean initHelper(Player *, Board, Boolean *);
Position *initReader(char[], Position *);
Boolean quitToMainMenu(char[]);
Boolean mainGame(Player *, Board);
Boolean mainGameReader(char[], Player *, Board);
void startupCommands();
Boolean move(Position, Player *, Direction, Board);
Boolean shoot(Player *, Direction *, Position, Board);
Direction *directionChecker(char[], Direction *);
void randomPos(Board, Player *);
void newLineRemover(char[]);

#endif
