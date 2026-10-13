#include "raylib.h"
#include <iostream>
using namespace std;

class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}

	void Update() {
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {

			speed_y *= -1;
		}
		if (x + radius >= GetScreenWidth() || x - radius <= 0) {
			speed_x *= -1;
		}
		
	}
	void Reset() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		speed_x *= -1; // Send it to the other player
	}
};

class Paddel {
protected:
	void LimitMovement() {
		if (y <= 0)
			y = 0;
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}


public:
	float x, y;
	float width, height;
	float speed;

	void Draw() {
		DrawRectangle(x, y, height, width, WHITE);
	}

	void Update() {
		if (IsKeyDown(KEY_UP))
			y = y - speed;
		if (IsKeyDown(KEY_DOWN))
			y = y + speed;
		
		LimitMovement();
	}
};

class cpuPaddele :public Paddel {
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y)
			y = y - speed;
		if (y + height / 2 <= ball_y)
			y = y + speed;

		LimitMovement();
	} 
};



Ball ball;
Paddel player;
cpuPaddele cpu;
int playerScore = 0;
int cpuScore = 0;

int main() {
	

	int sWidth = 1200;
	int sHeight = 800;


	InitWindow(sWidth, sHeight, "Pong Game");
	SetTargetFPS(60);

	ball.radius = 20;
	ball.x = sWidth/2;
	ball.y = sHeight / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	player.width = 120;
	player.height = 25;
	player.speed = 6;
	player.x = 10;
	player.y = sHeight / 2 - player.height / 2;

	cpu.width = 120;
	cpu.height = 25;
	cpu.speed = 6;
	cpu.x = GetScreenWidth() - 35;
	cpu.y = sHeight / 2 - cpu.height / 2;



	while (WindowShouldClose() == false) {

		
		// Updating
		BeginDrawing();
		ball.Update();
		player.Update();
		cpu.Update(ball.y);
		
		//Check Collisions with boundries
		if (ball.x + ball.radius >= GetScreenWidth()) {
			playerScore++;
			ball.Reset();
		}
		if (ball.x - ball.radius <= 0) {
			cpuScore++;
			ball.Reset();
		}

		//Check Collisions
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{player.x, player.y, player.width, player.height })){
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height })) {
			if (ball.speed_x > 0) ball.speed_x *= -1; // Bounce left
		}
			

		// Drawing
		ClearBackground(BLACK);
		DrawLine(sWidth / 2, 0, sWidth/2, sHeight, WHITE);
		DrawCircle(600, 400, 20, WHITE);
		ball.Draw();

		//scores
		DrawText(TextFormat("%d", playerScore), 300, 150, 40, WHITE);
		DrawText(TextFormat("%d", cpuScore), 900, 150, 40, WHITE);
		
		
		player.Draw();
		cpu.Draw();
		EndDrawing();



	}


	CloseWindow();
}