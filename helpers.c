/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Jia Jun Yong
 * Student number: s3688090
 */
#include "helpers.h"

void readRestOfLine()
{
	int ch;
	while(ch = getc(stdin), ch != EOF && ch != '\n')
	{ } /* Gobble each character. */

	/* Reset the error status of the stream. */
	clearerr(stdin);
}

ReadInputResult readInput(char * str, int num, FILE * stream)
{
	char * result;

	result = fgets(str, num, stream);
	if(result == NULL)
	{
		return ReadInputResultNull;
	}
	else if(str[strlen(str) - 1] != '\n')
	{
		readRestOfLine();
		return ReadInputResultOverflow;
	}
	else
	{
		str[strlen(str) - 1] = '\0';
		return ReadInputResultSuccess;
	}
}

ReadInputResult getInput(char * prompt, char * input, int inputSize)
{
	ReadInputResult readInputResult;

	while(TRUE)
	{
		printf("%s", prompt);
		readInputResult = readInput(input, inputSize, stdin);
		printf("\n");

		if(readInputResult != ReadInputResultSuccess)
		{
			printInvalidInput();
			continue;
		}

		return readInputResult;
	}
}

void printInvalidInput()
{
	printf("\n\nInvalid input. \n\n");
	readRestOfLine();
}

void enableWindowsCompatibility()
{
	/* Disable buffering on stdout - this is typically an issue on Windows. */
	setbuf(stdout, NULL);

	/* Disable buffering on stderr just in case. */
	setbuf(stderr, NULL);
}
