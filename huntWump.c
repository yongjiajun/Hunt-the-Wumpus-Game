/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Jia Jun Yong
 * Student number: s3688090
 */
#include "huntWump.h"

/* Show student information */
void showStudentInformation() { 
   printf("\n\n%s\nName: %s", INFO_HORILINE, STUDENT_NAME);
   printf("\nStudent ID: %s", STUDENT_ID);
   printf("\nEmail: %s", STUDENT_EMAIL);
   printf("\n%s\n\n", INFO_HORILINE);
}

/* main() that calls mainMenu() */
int main()
{
    mainMenu();
    return 0;
}

/* Display main menu of the game */
void mainMenu()
{
    char choice[MAX_LIMIT];
    printf("\nWelcome to Hunt the Wumpus\n");
    printf("--------------------\n");
    printf("1. Play Game\n2. Show student information\n3. Quit\n\n");
    printf("Please enter your choice: ");

    fgets(choice, MAX_LIMIT, stdin);

    /* convert '\n' into '\0' */
    newLineRemover(choice);

    if (strcmp(choice, PLAY_GAME) == SAME)
        game_PlayGame();
    else if (strcmp(choice, STUDENT_INFO) == SAME)
        showStudentInformation();
    else if (strcmp(choice, QUIT) == SAME)
    {
        printf("\nGood bye!\n\n");
        return;
    }
    else
        printInvalidInput();
    mainMenu();
}
