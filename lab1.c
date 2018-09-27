/***********************************************/
/* Spencer Goles COEN 11 Lab # 1               */
/* 19 May 2018                                 */
/* This program is a math test for 10 problems */
/***********************************************/

//Import needed libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Declare method
int main(void) 
{
	//Declare var and introduce game
	int correct = 0;
	printf("\nWelcome to the Math Game!\n");
	printf("Answer the questions and click enter.\n");
	//Seed srand() with time to ensure random numbers
	srand((int)time(NULL));
	//Declare for loop with 10 iterations
	for(int i = 0; i < 10;i++)
	{ 
		//Declare var and set for random numbers using rand()
		int quotient = rand() % 13;
		int divisor = rand() % 12+1;
		int input,denominator;
		denominator = divisor*quotient;
		printf("\n %d / %d \n", denominator, divisor); 
		printf("Enter Answer: \n");
		//Use scanf to collect user answer
		scanf("%d", &input);
		//Check if user input is correct and adjust correct count
		if(input == quotient)
		{
			printf("You are correct!\n");
			correct++;
		}
		else
		{
			printf("That's incorrect. The answer is %d.\n",quotient);
		}
	}
	//Print correct answers and return to terminal when done
	printf("\nYou were right on %i questions!\n",correct);
	return 0;
	
}


