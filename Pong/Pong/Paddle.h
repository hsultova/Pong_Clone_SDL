#pragma once

#include "GameManager.h"

class Paddle
{
public:
	Paddle(Texture* _texture);
	~Paddle();

	int GetSpeed() const;
	Position GetPosition();
	Position GetVelocity();

	//void SetPosition(Position _positon);
	//void SetVelocity(Position _positon);

	void UpdateVelocity(Direction _direction);
	void ResetPosition(int x, int y);

	void Update();
	void Render();

private:
	void Move();

private:
	Position m_position;
	Position m_velocity;

	Texture* m_texture;
	int m_speed;
};

