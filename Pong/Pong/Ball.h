#pragma once

#include "GameManager.h"
#include "Collider.h"

class Ball : public Collider
{
public:
	Ball(Position _position, Texture& _texture);
	~Ball();

	Position GetPosition() const;
	Position GetVelocity() const;
	int GetSpeed() const;

	void Update();
	void Render();

	void SetVelocity(const Position& _position);
	void ResetPosition();

private:
	void Move();

private:
	Position m_position;
	Position m_velocity;
	int m_speed = 7;

	Texture& m_texture;
};

