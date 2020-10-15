#include "Paddle.h"

Paddle::Paddle(Position _position, Texture& _texture)
	: Collider(ColliderBox{ _position.x, _position.y, (float)_texture.GetWidth(), (float)_texture.GetHeight() }, Type::dynamicCollider),
	m_position(_position), m_texture(_texture)
{
	m_initialPosition = _position;
	m_velocity = Position{ 0, 0 };
	m_speed = 10;
}

Paddle::~Paddle()
{
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

void Paddle::UpdateToWindow(int x, int y)
{
	m_position = Position{ m_position.x - x, m_position.y - y / 2 };
	UpdateCollisionBox(m_position.x - x, m_position.y - y / 2);
}

void Paddle::ResetPosition()
{
	m_position = m_initialPosition;
}

void Paddle::Update()
{
	Move();
	UpdateCollisionBox(m_position.x, m_position.y);
}

void Paddle::Render()
{
	m_texture.Render((int)m_position.x, (int)m_position.y);
}

void Paddle::Move()
{
	m_position.y += m_velocity.y;

	//If the dot went too far up or down
	if ((m_position.y < 5) || (m_position.y + m_texture.GetHeight() > GameManager::Get()->GetWindowHeight()))
	{
		//Move back
		m_position.y -= m_velocity.y;
	}
}
