#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include <raylib.h>
#include <raymath.h>

#include "stb_ds.h"


/* some useful global constants */
#define VEC2_DOWN   ((Vector2) {  0.f,  1.f })
#define VEC2_UP     ((Vector2) {  0.f, -1.f })
#define VEC2_LEFT   ((Vector2) { -1.f,  0.f })
#define VEC2_RIGHT  ((Vector2) {  1.f,  0.f })


/* game specific global constants */ 
#define GAME_TITLE "puffin game"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


/* project source files */
/* #include "something.c" */


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

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
