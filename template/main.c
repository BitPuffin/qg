#include <stdio.h>

#include <raylib.h>

/* project source files */
/* #include "something.c" */

#define GAME_TITLE "puffin game"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

	Vector2 pos = {};
	Vector2 size = { 40.f, 40.f };
	Color color = PURPLE;

	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		/* update */
		pos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) color = PURPLE;
		else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) color = YELLOW;
		else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) color = DARKBLUE;

		/* draw */
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawRectangleV(pos, size, color);

		DrawText("welcome to " GAME_TITLE, 10, 10, 20, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
