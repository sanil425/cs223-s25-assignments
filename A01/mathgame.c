/***************************************************
 * mathgame.c
 * Author: Sanil Kagalwala
 * Date: 23rd Jan 2025
 * Implements program that plays a math game with user. The user chooses the number of rounds and is asked to add two numbers  
 * between 1 and 9. Their final score will be displayed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

// variable decleration
int numQuestions;
int numCorrect = 0;
int minNum = 1;
int maxNum = 9;

// welcome message
printf("Welcome to the Math Game\n");

srand(time(NULL)); //  call once

printf("How many rounds do you want to play?\n");
scanf("%d", &numQuestions); 


if (numQuestions < 1) {
	printf("Game over! Invalid number of rounds inputted.\n");
	return 0;
}

// loop
for (int i = 0; i < numQuestions; i++) {
	// generate two random numbers between 1 and 9
	// rand 
	int num1 = rand() % maxNum + 1; 
	int num2 = rand() % (maxNum - minNum + 1) + 1;

	printf("%d + %d = ? ", num1, num2);
	
	int answer;
	scanf("%d", &answer); 

	if (answer == num1 + num2) {
		printf("Correct!\n");
		numCorrect++;
	} else {
		printf("Incorrect :(\n");
	}
}

printf("Game over! You answered %d/%d questions correctly.\n", numCorrect, numQuestions);

return 0;
  
}
