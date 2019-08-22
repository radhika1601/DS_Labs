/*!
Lab-1 Question 2
Author:
	Name - Radhika Garg
	Roll Number - 18114060
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *dq ;
int filled ;
int size ;
clock_t clk;

/*!
This function print size, filled and all elements of queue.
*/

void printdq()
{
	printf("The size of deque is %d\n", size);
	printf("Filled entires are %d\n", filled);
	printf("The entries filled in deque are : ");
	for (int i = 0; i < filled; ++i)
	{
		printf("%d ", dq[i]);
	}
	printf("\n\n");
}

/*!
this function add a element in front of queue 
 when queue is empty than size assign 1
*/

void addFront (int data)
{
	if (size==0)
	{
		size = 1;
    	dq = (int*) malloc(size * sizeof(int));
		filled= 1;
		dq[0] = data;
		return;
	}

	if(size > filled)
	{
		for(int i = filled-1; i >= 0; i--)
		{
			dq[i+1] = dq[i];
		}
		dq[0] = data;
		filled++;
	}
	else if(size == filled)
	{
		size *= 2;
    	dq = realloc(dq, size * sizeof(int));
		for(int i = filled-1; i>=0 ; i--)
		{
			dq[i+1] = dq[i];
		}		
		dq[0] = data;
		filled++;		
	}
}

/*!
this function add a element in back of queue 
 when queue is empty than size assign 1
*/

void addBack (int data)
{
	if (size==0)
	{
		size = 1;
    	dq = (int*) malloc(size * sizeof(int));
		filled= 1;
		dq[0] = data;
		return;
	}

	if(size > filled)
	{
		dq[filled] = data;
		filled++;
	}
	else if(size == filled)
	{
		size *= 2;
    	dq = realloc(dq, size * sizeof(int));
		dq[filled] = data;
		filled++;		
	}
}

/*!
 this function remove a element from back of queue 
 when queue is half filled then size redeue to half of its size.
*/

void removeBack()
{
	if(filled <= 0)
		printf("Deque is empty\n");
	else
	{
		filled-- ;
		if(size == filled*2)
			size = filled;
	}
}

/*!
 this function remove a element from front of queue 
 when queue is half filled then size redeue to half of its size.
*/

void removeFront()
{
	if(filled <= 0)
		printf("Deque is empty\n");
	else 
	{
		for (int i = 0; i < filled-1; ++i)
		{
			dq[i] = dq[i+1];
		}
		filled--;
		if(size == filled*2)
			size = filled;
	}
}

/*!
 this function print front element of queue
 */

void frontElement(){
	if(filled <= 0)
		printf("Deque is empty\n");
	else
	{
		printf("%d\n", dq[0]);
	}
}

/*!
 this function print back element of queue
 */

void backElement(){
	if(filled <= 0)
		printf("Deque is empty\n");
	else
	{
		printf("%d\n", dq[filled-1]);
	}
}

/*!
 this function call every time whenever any operatoin is finished.
 */

void menu()
{
	printf("Please select from the following choices.\n");
	printf("1. To add element in front.\n");
	printf("2. To add element from back\n");
	printf("3. To remove element from front\n");
	printf("4. To remove element from back\n");
	printf("5. To get the front element\n");
	printf("6. To get the last element\n");
	printf("7. To print the deque\n\n");

	int i;
	scanf("%d", &i);
	switch(i)
	{
		case 1: {
			int n;
			puts("Enter the number to insert");
			scanf("%d", &n);
			clk=clock();
			addFront(n);
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
		case 2: {
			int n;
			scanf("%d", &n);
			puts("Enter the number to insert");
			clk=clock();
			addBack(n);
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
		case 3: {
			clk=clock();
			removeFront();
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
		case 4:{
			clk=clock();
			removeBack();
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
		case 5:{ 
			clk=clock();
			frontElement();
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
		case 6:{ 
			clk=clock();
			backElement();
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
		case 7:{ 
			clk=clock();
			printdq();
			clk=clock()-clk;
			printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
			break;
		}
	}
}

/*!
 at starting first assign size and filled 0...
 */

int main()
{
	dq = NULL;
	size = 0;
	filled= 0;

	while(1)
	{
		menu();
	}
}