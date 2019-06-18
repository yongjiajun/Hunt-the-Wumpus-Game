/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Jia Jun Yong
 * Student number: s3688090
 */
#include "player.h"

/* Initialise player with selected position */
void player_Initialise(Player *player, Position position)
{
    player->position.x = position.x;
    player->position.y = position.y;
    player->numArrows = INIT_ARROW_COUNT;
}

/* Get next position */
Position player_GetNextPosition(Position position, Direction direction)
{
    Position newPos;
    newPos = position;
    if (direction == player_NORTH)
    {
        newPos.y--;
    }
    else if (direction == player_SOUTH)
    {
        newPos.y++;
    }
    else if (direction == player_EAST)
    {
        newPos.x++;
    }
    else if (direction == player_WEST)
    {
        newPos.x--;
    }
    return newPos;
}

/* Update player's position */
void player_UpdatePosition(Player *player, Position position)
{
    player->position.x = position.x;
    player->position.y = position.y;
}
