/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Jia Jun Yong
 * Student number: s3688090
 */
#include "board.h"

Board BOARD_1 =
	{
		{board_EMPTY, board_EMPTY, board_EMPTY, board_PIT, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY},
		{board_BATS, board_EMPTY, board_EMPTY, board_WUMPUS, board_EMPTY},
		{board_EMPTY, board_PIT, board_EMPTY, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_BATS, board_EMPTY, board_EMPTY}};

Board BOARD_2 =
	{
		{board_PIT, board_EMPTY, board_PIT, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_BATS, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY, board_BATS},
		{board_EMPTY, board_WUMPUS, board_EMPTY, board_EMPTY, board_EMPTY},
};

/* Load selected game board */
void board_Load(Board board, Board boardToLoad)
{
	int i, j;

	/* assigning each value from selected board to the boardToLoad */
	for (i = 0; i < BOARD_WIDTH; i++)
	{
		for (j = 0; j < BOARD_HEIGHT; j++)
		{
			boardToLoad[i][j] = board[i][j];
		}
	}
}

/* Place player on the game board */ 
Boolean board_PlacePlayer(Board board, Position position)
{
	int x, y;
	x = position.x;
	y = position.y;

	/* position validation */
	if (((x < BOARD_WIDTH && x >= 0) && (y <= BOARD_HEIGHT && y >= 0)) 
		&& (board[y][x] == board_EMPTY))
	{
		board[y][x] = board_PLAYER;
		return TRUE;
	}
	else
	{
		printf("\nUnable to place player at that position.\n");
		return FALSE;
	}
}

/* Move player on the board */
PlayerMove board_MovePlayer(Board board, Position playerPosition,
							Position nextPosition)
{
	int xOld, yOld, xNew, yNew, newPosition;
	Boolean xValid, yValid, valid;
	xOld = playerPosition.x;
	yOld = playerPosition.y;
	xNew = nextPosition.x;
	yNew = nextPosition.y;
	/* position validation */
	xValid = xNew < BOARD_WIDTH && xNew >= 0;
	yValid = yNew < BOARD_HEIGHT && yNew >= 0;
	valid = xValid && yValid;
	if (valid == TRUE)
	{
		newPosition = board[yNew][xNew];
		if (newPosition == board_PIT || newPosition == board_WUMPUS)
		{
			return board_PLAYER_KILLED;
		}
		else if (newPosition == board_BATS)
		{
			board[yOld][xOld] = board_TRAVERSED;
			return board_BAT_CELL;
		}
		else if (newPosition == board_EMPTY || newPosition == board_TRAVERSED)
		{
			board[yOld][xOld] = board_TRAVERSED;
			board[yNew][xNew] = board_PLAYER;
			return board_PLAYER_MOVED;
		}
	}
	else
	{
		return board_OUTSIDE_BOUNDS;
	}
	return board_PLAYER_MOVED;
}

/* Arrow fired position validation */
ArrowHit board_FireArrow(Board board, Position position)
{
	int x, y, pos;
	Boolean xValid, yValid, valid;
	x = position.x;
	y = position.y;
	xValid = x < BOARD_WIDTH && x >= 0;
	yValid = y < BOARD_HEIGHT && y >= 0;
	valid = xValid && yValid;
	if (valid == TRUE)
	{
		pos = board[y][x];
		if (pos == board_WUMPUS)
		{
			return board_WUMPUS_KILLED;
		}
	}
	else
	{
		return board_ARROW_OUTSIDE_BOUNDS;
	}
	/* arrow is missed when position passes the validation but
	 * wumpus doesn't exist */
	return board_ARROW_MISSED;
}

/* Display board */
void board_Display(Board board)
{
	int i, j, temp;
	char *print;
	printf("\n    0  1  2  3  4\n");
	printf(HORI_LINE);
	/* loops through board array to display board */
	for (i = 0; i < BOARD_WIDTH; i++)
	{
		printf("%d |", i);
		for (j = 0; j < BOARD_HEIGHT; j++)
		{
			temp = board[i][j];
			if (temp == board_TRAVERSED)
				print = TRAVERSED_OUTPUT;
			else if (temp == board_PLAYER)
				print = PLAYER_OUTPUT;
			else
				print = EMPTY_OUTPUT;
			printf("%s|", print);
		}
		printf("\n%s", HORI_LINE);
	}
}

/* Display warnings when player is surrounded by deadly elements */
void board_DisplayWarnings(Board board, Position position)
{
	int i, j, x, y, temp;
	x = position.x;
	y = position.y;
	/* loops through board array to scan for danger sources around player */ 
	for (i = x - ARRAY_BOUNDARY; i <= x + ARRAY_BOUNDARY; i++)
	{
		for (j = y - ARRAY_BOUNDARY; j <= y + ARRAY_BOUNDARY; j++)
		{
			temp = board[j][i];
			if (temp == board_BATS)
			{
				printf("You hear flapping!\n");
			}
			else if (temp == board_PIT)
			{
				printf("You feel a breeze!\n");
			}
			else if (temp == board_WUMPUS)
			{
				printf("You smell a wumpus!\n");
			}
		}
	}
}

