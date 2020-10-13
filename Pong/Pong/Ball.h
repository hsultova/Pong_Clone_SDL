#pragma once

#include "GameManager.h"

class Ball
{
public:
	Ball(Texture& _texture);
	~Ball();

	void Update();
	void Render();

private:
	void Move();

private:
	Position m_position;
	Position m_velocity;

	Texture& m_texture;
};

