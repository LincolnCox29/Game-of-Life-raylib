#include "stddef.h"
#include "field.h"
#include "stdio.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "raylib.lib")
#include "include/raylib.h"

#define FIELD_SWAP_BUFFER(buffer, field)    \
{                                           \
	Field tmp = field;                      \
	field = buffer;                         \
	buffer = tmp;	                        \
}

typedef struct msgsManager
{
	bool isRun;
	bool isCellChanged;
} msgsManager; 

void checkMsgs(msgsManager* man)
{
	switch (GetKeyPressed())
	{
		case KEY_SPACE:
			man->isRun = !man->isRun;
			break;
		case KEY_ESCAPE:
			CloseWindow();
			break;
		default:
			break;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		man->isCellChanged = true;
}

int main()
{
	msgsManager man = {0};

	Field field = newField();
	Field buffer = newField();

	InitWindow(800, 800, "game of life raylib");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		checkMsgs(&man);

		BeginDrawing();

		ClearBackground(BLACK);

		drawField(field);

		if (man.isCellChanged && !man.isRun)
		{
			changeCell(field);
			man.isCellChanged = false;
		}

		EndDrawing();

		if (man.isRun)
		{
			nextField(field, buffer);
			FIELD_SWAP_BUFFER(buffer, field);
			WaitTime(0.3);
		}
	}
	freeField(field);
	return 0;
}


