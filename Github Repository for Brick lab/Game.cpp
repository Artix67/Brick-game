#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
	for (int x = 0; x < brickVector.size(); x++) {

		brickVector[x].width = 10;
		brickVector[x].height = 3;
		brickVector[x].x_position = brickVector[x].x_position + 15;
		brickVector[x].y_position = 5;
		brickVector[x].doubleThick = true;
		brickVector[x].color = ConsoleColor::DarkGreen;
	}
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering should be done between the locks in this function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks
	
	for (int x = 0; x < brickVector.size(); x++) {

		brickVector[x].Draw();
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks

	for (int x = 0; x < brickVector.size(); x++) {

		if (brickVector[x].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			brickVector[x].color = ConsoleColor(brickVector[x].color - 1);
			ball.y_velocity *= -1;
		}

		if (brickVector[x].color == ConsoleColor::DarkGreen - 3) {
			brickVector.erase(brickVector.begin() + x);
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display victory text with R to reset

	if (brickVector.empty()) {

	}
	
	// TODO #7 - If ball touches bottom of window, pause ball and display defeat text with R to reset
}
