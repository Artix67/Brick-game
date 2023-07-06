#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	
	Box brick0;
	Box brick1;
	Box brick2;
	Box brick3;
	Box brick4;

	std::vector<Box> brickVector = { brick0, brick1, brick2, brick3, brick4 };

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};