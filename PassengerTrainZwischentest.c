#include <stdio.h>
#incldue <stdlib.h>

enum type { passenger, sleeper, diner };

struct carriage { int capacity;
    enum type type;
};

struct train {
    int length;
    struct carriage carriages[10];
};

void printCarriage(struct carriage c)
{
	char type = 'P';
	if(c.type == sleeper)
		type = 'S';
	else if(c.type == diner)
		type = 'D';

	printf("[%c:%03d]", type, c.capacity);
}

void printTrain(struct train *t)
{
	printf("\nTrain: ");
	if(t->length == 0)
	{
		printf("No Carriages!");
		return;
	}

	for(int i = 0; i < t->length; i++)
	{
		printf("%d:", i);
		printCarriage(t->carriages[i]);
		if(i != t->length - 1)
		printf("-");
	}
	

	printf(" Length: %d", t->length);
}

char getMenu()
{
    char input;
    printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x): ");
    scanf(" %c", &input);

    while(input != 'p' && input != 'n' && input !='s' && input != 'x')
    {
        printf("\nInput invalid! Try again: ");
        scanf(" %c", &input);
    }
    return input;
}

struct carriage getCarriage()
{
    struct carriage new;

    char input;
    int capacity;

    printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d): ");
    scanf(" %c", &input);

    while (input != 'p' && input != 's' && input != 'd')
	{
		printf("\nInput invalid! Try again: ");
		scanf(" %c", &input);
	}

	switch(input)
	{
		case 'p':
			new.type = passenger;
			break;
		case 's':
			new.type = sleeper;
			break;
		case 'd':
			new.type = diner;
			break;
	}

    printf("\nChoose capacity (20 - 130): ");
    scanf (" %d", &capacity);
	while(capacity > 130 || capacity < 20)
	{
		printf("\nInput invalid! Try again: ");
		scanf (" %d", &capacity);
	}
    new.capacity = capacity;

	printf("\n");
    return new;
}

int getPosition(int length)
{
	int position;
    printf("Choose position for the new carriage (0-%d): ", length);
    scanf (" %d", &position);

	while(position < 0 || position > length)
	{
		printf("\nInput invalid! Try again: ");
		scanf (" %d", &position);
	}

	return position;
}

int insertCarriage(struct train *t, int pos, struct carriage c)
{
	int length = t->length;
	if(length == 10)
		return -1;

	if(pos < 0 || pos > length)
		return -2;

	if(c.type == diner)
	{
		if(length < 2 || pos == 0 || pos == length)
			return -3;
		else if(t->carriages[pos - 1].type != passenger || t->carriages[pos].type != passenger)
			return -3;
	}

	for(int i = length; i > pos; i--)
		t->carriages[i] = t->carriages[i - 1];

	t->carriages[pos] = c;
	t->length++;

	return 0;
}

int sumCapacity(struct train *t, enum type type)
{
	int sum = 0;
	for(int i = 0; i < t->length; i++)
	{
		struct carriage c = t->carriages[i];
		if(c.type == type)
			sum += c.capacity;
	}

	return sum;
}

void printTrainStats(struct train *t)
{
	printTrain(t);
	printf("\nCapacities: ");
	printf("\n  Passenger: %d", sumCapacity(t, passenger));
	printf("\n  Sleeper: %d", sumCapacity(t, sleeper));
    int dinercapacity = sumCapacity(t, diner);
	printf("\n  Diner: %d", dinercapacity);
	if(dinercapacity > 60)
		printf(" - invalid");
}


int main()
{
	struct train t;
	t.length = 0;

	while(1)
	{
		char input = getMenu();
		switch(input)
		{
			case 'p':
				printTrain(&t);
				break;
			case 'n':
			{
				struct carriage c = getCarriage();
				int position = getPosition(t.length);
				int result = insertCarriage(&t, position, c);
				switch(result)
				{
					case -1:
						printf("\nError: Train too long!");
						break;
					case -2:
						printf("\nError: Position not possible!");
						break;
					case -3:
						printf("\nError: Diner only possible between two passenger carriages!");
						break;
				}
			}
				break;
			case 's':
				printTrainStats(&t);
				break;
			case 'x':
				return 0;
		}
	}
}
