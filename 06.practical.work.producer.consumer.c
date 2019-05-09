#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 10
typedef struct product
{
	char type;  // 0=burito, 1=taco
	int amount; 
	char unit;  
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
void initBurito(item *smt) {
	smt->type = 0;
	smt->amount = 0;
	smt->unit = 0;
}
void produce(item *i)
{
	while ((first + 1) % BUFFER_SIZE == last)
	{
		printf("No free buffer item!\n");
		return;
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	printf("First = %d\n", first);
}
void consume()
{
	item *i = malloc(sizeof(item));
	while (first == last)
	{
		printf("Nothing to consume!\n");
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	printf("Last = %d\n", last);
	return;
}

int main()
{
	int option = 0;
	item *burito, beef, *taco, fish;
	burito = &beef;
	taco = &fish;
	printf("Welcome to Wrap&Roll food truck ! \n");
	printf("Today we have: Beef burito and fish taco \n");
	printf("Burito: 1 || Taco: 2 \n");
	while (true)
	{
		/* code */
		scanf("%d", &option);
		if (option == 1)
		{
			printf("Burito serving in 5 seconds\n");
			initBurito(burito);
			produce(burito);
			initBurito(burito);
			produce(burito);
			printf("Consuming...\n");
			consume();
			break;
		}
		else if (option == 2)
		{
			printf("Taco's coming in 2 seconds\n");
			produce(taco);
			produce(taco);
			printf("Consuming...\n");
			consume();
			break;
		}
		else
		{
			printf("Try again!\n");
			printf("Burito: 1 || Taco: 2\n");
		}
	}
	return 0;
}
