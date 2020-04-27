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
#define PAUSE_DURATION 1.0

#define BALL_VEL 500.f
#define BOUNCE_VEL_INCREASE 50.f


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

bool shouldPause;
float pause_time;

Vector2 pos;
Vector2 enemypos;
	
Vector2 ballpos;
Vector2 ballvel;

int bouncecount;

void reset_state()
{
	bouncecount = 0;
	shouldPause = true;
	pause_time = 0.0f;

	pos = (Vector2) { PLAYER_X, SCREEN_HEIGHT / 2.f };
	enemypos = (Vector2) { ENEMY_X, SCREEN_HEIGHT / 2.f} ;
	
	ballpos = (Vector2) {
		SCREEN_WIDTH / 2.f - BALL_SIZE / 2.f,
		SCREEN_HEIGHT / 2.f - BALL_SIZE / 2.f,
	};
	ballvel.y = randfloat() * 2.f - 1.f;
	ballvel.y *= 0.95;
	ballvel.x = 1.0 - ballvel.y;
	ballvel = Vector2Normalize(ballvel);
	ballvel = Vector2Scale(ballvel, BALL_VEL);
}

float calculate_ball_y_vel(Vector2 paddlepos, Vector2 ballpos)
{
	float py = paddlepos.y;
	float by = ballpos.y - py + BALL_SIZE;
	float mid = (BALL_SIZE / 2.f) + (PADDLE_HEIGHT / 2.f);
	return (by - mid) * 0.95; /* so it never quite becomes -1 or 1 */
}


void update()
{
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
			ballvel.y = calculate_ball_y_vel(pos, ballpos);
			ballvel.x = abs(1.0 - ballvel.y);
			ballvel = Vector2Normalize(ballvel);
			ballvel = Vector2Scale(ballvel, BALL_VEL + BOUNCE_VEL_INCREASE * bouncecount++);
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
			ballvel.y = calculate_ball_y_vel(enemypos, ballpos);
			ballvel.x = -abs(1.0 - ballvel.y);
			ballvel = Vector2Normalize(ballvel);
			ballvel = Vector2Scale(ballvel, BALL_VEL + BOUNCE_VEL_INCREASE * bouncecount++);
		}
	} else if (ballpos.x < 0.f || ballpos.x > SCREEN_WIDTH) {
		reset_state();
	}
}


int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

	reset_state();

	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		if(shouldPause) {
			pause_time += GetFrameTime();
			if (pause_time >= PAUSE_DURATION) {
				shouldPause = false;
			}
		} else {
			update();
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
