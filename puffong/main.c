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
#define GAME_TITLE "puffong"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define PADDLE_WIDTH 32
#define PADDLE_HEIGHT 128
#define INSET 10.f
#define PLAYER_X INSET
#define MIN_Y INSET
#define MAX_Y (SCREEN_HEIGHT - (PADDLE_HEIGHT + INSET))
#define ENEMY_X SCREEN_WIDTH - (INSET + PADDLE_WIDTH)

#define BALL_SIZE 16

/* project source files */
/* #include "something.c" */

float randfloat()
{
	float a = (float)rand();
	float b = (float)RAND_MAX;
	return a / b;
}

static Vector2 constrain_paddle(Vector2 v)
{
	v.y = fmin(v.y, MAX_Y);
	v.y = fmax(v.y, MIN_Y);
	return v;
}

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

	Vector2 pos = { PLAYER_X, SCREEN_HEIGHT / 2.f };
	Vector2 enemypos = { ENEMY_X, SCREEN_HEIGHT / 2.f} ;
	
	Vector2 ballpos = {
		SCREEN_WIDTH / 2.f - BALL_SIZE / 2.f,
		SCREEN_HEIGHT / 2.f - BALL_SIZE / 2.f,
	};
	Vector2 ballvel = {
		-500.f,
		randfloat() * 10.f * 100.f,
	};

	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		/* update */
		Vector2 mousepos = GetMousePosition();
		pos.y = mousepos.y - PADDLE_HEIGHT / 2.f;
		pos = constrain_paddle(pos);

		enemypos.y = pos.y;

		Vector2 ballup = Vector2Scale(ballvel, GetFrameTime());
		ballpos = Vector2Add(ballpos, ballup);
		if (ballpos.y < INSET) {
			ballvel.y = -ballvel.y;
		} else if (ballpos.y > SCREEN_HEIGHT - INSET) {
			ballvel.y = -ballvel.y;
		}
		if (ballpos.x < PLAYER_X + PADDLE_WIDTH && ballpos.x > PLAYER_X + PADDLE_WIDTH / 2.f) {
			Rectangle pr = {
				.x = pos.x,
				.y = pos.y,
				.width = PADDLE_WIDTH,
				.height = PADDLE_HEIGHT,
			};
			Rectangle br = {
				.x = ballpos.x,
				.y = ballpos.y,
				.width = BALL_SIZE,
				.height = BALL_SIZE,
			};
			if (CheckCollisionRecs(pr, br)) {
				ballvel = Vector2Negate(ballvel);
			}
		} else if (ballpos.x > ENEMY_X && ballpos.x < ENEMY_X + PADDLE_WIDTH / 2.f) {
			Rectangle er = {
				.x = enemypos.x,
				.y = enemypos.y,
				.width = PADDLE_WIDTH,
				.height = PADDLE_HEIGHT,
			};
			Rectangle br = {
				.x = ballpos.x,
				.y = ballpos.y,
				.width = BALL_SIZE,
				.height = BALL_SIZE,
			};
			if (CheckCollisionRecs(er, br)) {
				ballvel = Vector2Negate(ballvel);
			}
		}


		/* draw */
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawRectangle(pos.x, pos.y, PADDLE_WIDTH, PADDLE_HEIGHT, BLACK);
		DrawRectangle(enemypos.x, enemypos.y, PADDLE_WIDTH, PADDLE_HEIGHT, BLACK);
		DrawRectangle(ballpos.x, ballpos.y, BALL_SIZE, BALL_SIZE, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
