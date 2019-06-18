/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Jia Jun Yong
 * Student number: s3688090
 */
#include "game.h"

/* Main function of game.c that ensures flow control,
 * returns to main menu when requested */
void game_PlayGame()
{
	Boolean returnToMenu, *successPointer, success; 
	Player player;
	Board boardToLoad;
	success = FALSE;
	successPointer = &success;
	srand(0);
	returnToMenu = FALSE;
	startupCommands();
	/* keep running till board is loaded */
	while (*successPointer != TRUE)
	{
		returnToMenu = boardLoadHelper(boardToLoad, successPointer);
	}
	/* continue initiating player and its position when return to main menu 
	 * isn't requested */
	if (returnToMenu == FALSE)
	{
		/* keep running till player is initialised */
		do
		{
			returnToMenu = initHelper(&player, boardToLoad, successPointer);
		} while (*successPointer != TRUE);
	}
	else
		return;
	/* continue to main game if return to main menu isn't requested*/
	if (returnToMenu == FALSE)
	{
		/* the mainGame function will call itself recursively till game ends */
		returnToMenu = mainGame(&player, boardToLoad);
	}
}

/* Displays usable commands accordingly to stages in the program */
void commandsAtStage(char stage)
{
	char *numCommands;
	if (stage == LOAD_STATE || stage == INIT_STATE)
		numCommands = "two";
	else if (stage == GAME_STATE)
		numCommands = "three";

	printf("\nAt this stage of the program, only %s commands are acceptable:\n"
		, numCommands);
	if (stage == LOAD_STATE)
		printf(" load <g>");
	else if (stage == INIT_STATE)
		printf(" init <x>,<y>");
	else if (stage == GAME_STATE)
		printf(" <direction>\n shoot <direction>");
	printf("\n quit\n\n");
	if (stage == GAME_STATE)
	{
		printf("Where <direction> is one of: north,n,south,s,east,e,west,w\n");
		printf("\nPlease enter your choice: ");
	}
}

/* Display game startup commands */
void startupCommands()
{
	printf("\n\nYou can use the following commands to play the game:\n\n");
	printf("load <g>\n g: number of the game board to load (either 1 or 2)\n");
	printf("init <x>,<y>\n");
	printf(" x: horizontal position of the player on the board ");
	printf("(between 0 & 4)\n");
	printf(" y: vertical position of the player on the board");
	printf("(between 0 & 4)\n");
	printf("north (or n)\nsouth (or s)\neast (or e)\nwest (or w)\nquit\n\n");
	printf("Press enter to continue... ");
	readRestOfLine();
}

/* Take input from user for loading the selected board */
Boolean boardLoadHelper(Board board, Boolean *success)
{
	char str[MAX_LIMIT], *selection;
	Boolean quit;
	*success = TRUE;
	commandsAtStage(LOAD_STATE);
	fgets(str, MAX_LIMIT, stdin);

	/* check if quit to main menu is requested */
	quit = quitToMainMenu(str);

	if (quit == TRUE)
	{
		return TRUE;
	}
	selection = boardLoadReader(str, board);
	if (selection == NULL)
	{
		*success = FALSE;
		return FALSE;
	}
	else if (strcmp(selection, BOARD_SELECTION_1) == SAME)
	{
		board_Load(BOARD_1, board);
	}
	else if (strcmp(selection, BOARD_SELECTION_2) == SAME)
	{
		board_Load(BOARD_2, board);
	}
	printf("\nBoard successfully loaded\n");
	return FALSE;
}

/* Validate user's input and return the selected board number */
char* boardLoadReader(char command[], Board board)
{
	/* check if command entered is "load" */
	char *loadArg, *boardSelection;

	/* Convert '/n' into a NULL pointer */
	newLineRemover(command);

	loadArg = strtok(command, STRING_SPACE);
	boardSelection = strtok(NULL, STRING_SPACE);
	
	if (boardSelection != NULL){
		if ((strcmp(loadArg, COMMAND_LOAD) == SAME) && 
			((strcmp(boardSelection, BOARD_SELECTION_1) == SAME) || 
			(strcmp(boardSelection, BOARD_SELECTION_2) == SAME)))
		{
			/* returns board selection */
			return boardSelection;
		}
	}
	printInvalidInput();
	/* return NULL if input is invalid */
	return NULL;
	
}

/* Take user's input and initialise player & its position */ 
Boolean initHelper(Player *player, Board board, Boolean *success)
{
	Boolean quit;
	char str[MAX_LIMIT];
	Position *pointer, position;
	*success = TRUE;
	pointer = &position;
	commandsAtStage(INIT_STATE);
	fgets(str, MAX_LIMIT, stdin);
	quit = quitToMainMenu(str);

	if (quit == TRUE)
	{
		return TRUE;
	}
	pointer = initReader(str, pointer);

	/* NULL pointer indicates input validation is failed */
	if (pointer == NULL)
	{
		*success = FALSE;
	}
	else
	{
		/* check if position inputted is valid */
		if (board_PlacePlayer(board, position) == TRUE)
		{
			player_Initialise(player, position);
		}
		else
		{
			*success = FALSE;
		}
	}
	return FALSE;
}

/* Validate user's input and return player's initial position */
Position *initReader(char command[], Position *pointer)
{
	/* check if command entered is "init" */
	char *initArg, *positionX, *positionY;
	newLineRemover(command);
	initArg = strtok(command, STRING_SPACE);
	positionX = strtok(NULL, STRING_COMMA);
	positionY = strtok(NULL, STRING_COMMA);

	/* input validation */
	if (positionX != NULL && positionY != NULL){
		if ((strcmp(initArg, COMMAND_INIT) == SAME) && 
			isdigit(positionX[STRING_FIRSTCHAR]) && 
			isdigit(positionY[STRING_FIRSTCHAR]))
		{
			/* convert char inputted to int */
			pointer->x = atoi(&positionX[STRING_FIRSTCHAR]);
			pointer->y = atoi(&positionY[STRING_FIRSTCHAR]);
			return pointer;
		}
	}
	printInvalidInput();
	pointer = NULL;
	return pointer;
}

/* Take command from user and ensure flow control of the game */
Boolean mainGame(Player *player, Board board)
{
	Boolean quit, finish;
	char str[MAX_LIMIT];
	board_Display(board);
	commandsAtStage(GAME_STATE);
	fgets(str, MAX_LIMIT, stdin);
	quit = quitToMainMenu(str);
	if (quit == TRUE)
	{
		return TRUE;
	}

	/* check if game is finished */
	finish = mainGameReader(str, player, board);
	if (finish == FALSE)
	{
		mainGame(player, board);
	}
	return FALSE;
}

/* Verify inputs and execute accordingly */
Boolean mainGameReader(char command[], Player *player, Board board)
{
	/* tempStr checks if input is equal to "shoot" */
	char *firstArg, *shootDirArg;
	Position tempPos;
	Boolean success;
	Direction direction, *dirPointer;
	dirPointer = &direction;
	success = FALSE;
	tempPos = player->position;

	/* Convert '/n' into a NULL pointer */
	newLineRemover(command);

	firstArg = strtok(command, STRING_SPACE);

	/* Check if first argument is shoot, if not, move player. */
	if (strcmp(firstArg, COMMAND_SHOOT) == SAME)
	{
		shootDirArg = strtok(NULL, STRING_SPACE);
		if (shootDirArg == NULL)
		{
			printInvalidInput();
		}
		else{
			dirPointer = directionChecker(shootDirArg, dirPointer);
			success = shoot(player, dirPointer, tempPos, board);
		}
	}
	else
	{
		dirPointer = directionChecker(firstArg, dirPointer);
		if (dirPointer == NULL)
		{
			printInvalidInput();
		}
		success = move(tempPos, player, direction, board);
	}
	return success;
}

/* Validate shoot command and execute accordingly */
Boolean shoot(Player *player, Direction *shootDir, Position tempPos, Board board)
{
	ArrowHit arrowHit;
	if (player->numArrows == 0)
	{
		printf("\nYou don't have any arrows to fire.\n");
	}
	else
	{
		if (shootDir == NULL)
		{
			printInvalidInput();
		}
		else
		{
			/* locate the position where the arrow's gonna hit,
			 * then verify the position */ 
			tempPos = player_GetNextPosition(tempPos, *shootDir);
			arrowHit = board_FireArrow(board, tempPos);
			if (arrowHit == board_WUMPUS_KILLED)
			{
				printf("\nYou killed the Wumpus!\n");
				return TRUE;
			}
			else if (arrowHit == board_ARROW_OUTSIDE_BOUNDS)
			{
				printf("\nUnable to fire arrow in that direction.\n");
			}
			else if (arrowHit == board_ARROW_MISSED)
			{
				player->numArrows--;
				printf("\nMissed. You now have %d arrows.\n", 
					player->numArrows);
			}
		}
	}
	return FALSE;
}

/* Validate shoot command and execute accordingly */
Boolean move(Position tempPos, Player *player, Direction direction, 
	Board board){
		PlayerMove playerMove;
		tempPos = player_GetNextPosition(tempPos, direction);
		playerMove = board_MovePlayer(board, player->position, tempPos);
		if (playerMove == board_PLAYER_MOVED)
		{
			player_UpdatePosition(player, tempPos);
			board_DisplayWarnings(board, player->position);
			printf("\nPlayer moved.\n");
		}
		else if (playerMove == board_PLAYER_KILLED)
		{
			board_DisplayWarnings(board, player->position);
			printf("\nPlayer killed!\n");
			return TRUE;
		}
		else if (playerMove == board_BAT_CELL)
		{
			/* relocate player to random location */
			randomPos(board, player);
			board_DisplayWarnings(board, player->position);
			printf("\nBat cell!\n");
		}
		else if (playerMove == board_OUTSIDE_BOUNDS)
		{
			printf("\nUnable to move - outside bounds.\n");
		}
	return FALSE;
}

/* Randomise player's position when player encounters bat cell */
void randomPos(Board board, Player *player){
	Boolean randomed;
	Position randomedPos;
	randomed = FALSE;
	
	/* verify position randomed is valid */
	while (randomed != TRUE)
	{
		int xNew, yNew, newPosition;

		/* generate a new position */ 
		xNew = rand() % BOARD_HEIGHT;
		yNew = rand() % BOARD_WIDTH;
		newPosition = board[yNew][xNew];
		
		if (newPosition == board_EMPTY || 
			newPosition == board_TRAVERSED)
		{
			randomed = TRUE;
			randomedPos.x = xNew;
			randomedPos.y = yNew;
			board[yNew][xNew] = board_PLAYER;
			break;
		}
		/* else, runs till a position randomed is valid */
	}
	player_UpdatePosition(player, randomedPos);
}

/* Validate direction inputted */
Direction* directionChecker(char command[], Direction *pointer)
{
	if (strcmp(command, COMMAND_NORTH) == SAME ||
		strcmp(command, COMMAND_NORTH_SHORTCUT) == SAME)
	{
		*pointer = player_NORTH;
	}
	else if (strcmp(command, COMMAND_SOUTH) == SAME ||
			 strcmp(command, COMMAND_SOUTH_SHORTCUT) == SAME)
	{
		*pointer = player_SOUTH;
	}
	else if (strcmp(command, COMMAND_EAST) == SAME ||
			 strcmp(command, COMMAND_EAST_SHORTCUT) == SAME)
	{
		*pointer = player_EAST;
	}
	else if (strcmp(command, COMMAND_WEST) == SAME ||
			 strcmp(command, COMMAND_WEST_SHORTCUT) == SAME)
	{
		*pointer = player_WEST;
	}
	else
	{
		/* if verification fails, returns NULL pointer */
		pointer = NULL;
	}
	return pointer;
}

/* Check if quit to main menu is requested */
Boolean quitToMainMenu(char command[])
{
	newLineRemover(command);
	if (strcmp(command, COMMAND_QUIT) == SAME)
		return TRUE;
	else
		return FALSE;
}

/* Convert '/n' into a NULL pointer */
void newLineRemover(char command[])
{
	char *newLineRemove;
	/* don't perform '\n' removal when user only inputs new line */
	if (strcmp(command, "\n\0") == SAME)
	{
		return;
	}
    else if ((newLineRemove = strchr(command, STRING_NEWLINE)) != NULL)
        *newLineRemove = STRING_NULL;
}
