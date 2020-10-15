#pragma once

#include "GameManager.h"
#include "Collider.h"

class Paddle : public Collider
{
public:
	Paddle(Position _position, Texture& _texture);
	~Paddle();

	int GetSpeed() const;
	Position GetPosition();
	Position GetVelocity();

	void UpdateVelocity(Direction _direction);
	void UpdateToWindow(int x, int y);
	void ResetPosition();

	void Update();
	void Render();

private:
	void Move();

private:
	Position m_position;
	Position m_initialPosition;
	Position m_velocity;

	Texture& m_texture;
	int m_speed;
};

