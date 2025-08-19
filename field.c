#include "stddef.h"
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "field.h"
#include "raylib.h"

#define CELL_SIZE 8

void freeField(Field field)
{
	if (field == NULL) {
		return;
	}
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		free(field[i]);
	}
	free(field);
}

void drawField(Field field)
{
	for (int c = 0; c < FIELD_SIZE; c++)
	{
		for (int r = 0; r < FIELD_SIZE; r++)
		{
			DrawRectangle(
				c * CELL_SIZE, r * CELL_SIZE, 
				CELL_SIZE - 1, CELL_SIZE - 1, 
				field[c][r] == DEAD ? WHITE : RED);
		}
	}
}

Field newField()
{
	Field field = malloc((FIELD_SIZE) * sizeof(char*));
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		field[i] = malloc((FIELD_SIZE) * sizeof(char));
		if (!field[i])
		{
			perror("[ERROR] Memory allocation failed");
			freeField(field);
			return NULL;
		}
		for (int c = 0; c < FIELD_SIZE; c++)
		{
			field[i][c] = DEAD;
		}
	}
	return field;
}

void nextField(Field field, Field buffer)
{
	int nextDoors;
	for (int c = 0; c < FIELD_SIZE; c++)
	{
		for (int r = 0; r < FIELD_SIZE; r++)
		{
			nextDoors = 0;
			for (int co = c - 1; co < c + 2; co++)
			{
				for (int ro = r - 1; ro < r + 2; ro++)
				{
					if ((co == c && ro == r)        ||
						 co >= FIELD_SIZE || co < 0 ||
						 ro >= FIELD_SIZE || ro < 0)
						continue;

					if (field[co][ro] == ALIVE)
						nextDoors++;
				}
			}

			buffer[c][r] =
				(!IS_ALIVE(field[c][r]) && nextDoors == 3) ||
				  IS_ALIVE(field[c][r]) && (nextDoors == 3 || nextDoors == 2);
		}
	}
}

void changeCell(Field field)
{
	char* CellPtr = 
		&(field[(int)(GetMouseX() / CELL_SIZE)][(int)(GetMouseY() / CELL_SIZE)]);
	*CellPtr = !*CellPtr;
}