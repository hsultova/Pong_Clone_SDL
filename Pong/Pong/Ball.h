#pragma once

#include "GameManager.h"

class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render();

private:
	void Move();

private:
	Position m_position;
	Position m_velocity;
};

