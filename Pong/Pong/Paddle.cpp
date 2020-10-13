#include "Paddle.h"

Paddle::Paddle(Texture* _texture) :m_texture(_texture)
{
	m_position = Position{ GameManager::Get()->GetWindowWidth() - 30.0f, GameManager::Get()->GetWindowHeight() / 2.0f - m_texture->GetHeight() / 2 };
	m_velocity = Position{ 0, 0 };
	m_speed = 10;
}

Paddle::~Paddle()
{
	m_texture = nullptr;
}

int Paddle::GetSpeed() const
{
	return m_speed;
}

Position Paddle::GetPosition()
{
	return m_position;
}

Position Paddle::GetVelocity()
{
	return m_velocity;
}

//void Paddle::SetPosition(Position _positon)
//{
//	m_position = _positon;
//}
//
//void Paddle::SetVelocity(Position _positon)
//{
//	m_velocity = _positon;
//}

void Paddle::UpdateVelocity(Direction _direction)
{
	if (_direction == Direction::up)
	{
		m_velocity.y -= m_speed;

	}
	else if (_direction == Direction::down)
	{
		m_velocity.y += m_speed;
	}
}

void Paddle::ResetPosition(int x, int y)
{
	m_position = Position{ m_position.x - x, m_position.y - y / 2 };
}

void Paddle::Update()
{
	Move();
}

void Paddle::Render()
{
	m_texture->Render(m_position.x, m_position.y);
}

void Paddle::Move()
{
	m_position.y += m_velocity.y;

	//If the dot went too far up or down
	if ((m_position.y < 5) || (m_position.y + m_texture->GetHeight() > GameManager::Get()->GetWindowHeight()))
	{
		//Move back
		m_position.y -= m_velocity.y;
	}
}
