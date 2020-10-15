#include "Ball.h"


Ball::Ball(Position _position, Texture& _texture)
	: Collider(ColliderBox{ _position.x, _position.y, (float)_texture.GetWidth(), (float)_texture.GetHeight() }, Type::dynamicCollider),
	m_position(_position), m_texture(_texture)
{
	m_velocity = Position{ 0, 0 };
}

Ball::~Ball()
{
}

Position Ball::GetPosition() const
{
	return m_position;
}

Position Ball::GetVelocity() const
{
	return m_velocity;
}

void Ball::Update()
{
	Move();
	UpdateCollisionBox(m_position.x, m_position.y);
}

void Ball::Move()
{
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
}

void Ball::Render()
{
	m_texture.Render((int)m_position.x, (int)m_position.y);
}

void Ball::UpdateVelocity(Direction _direction)
{
	if (_direction == Direction::up)
	{
		m_velocity.y -= m_speed;
	}
	else if (_direction == Direction::down)
	{
		m_velocity.y += m_speed;
	}
	else if (_direction == Direction::left)
	{
		m_velocity.x -= m_speed;
	}
	else if (_direction == Direction::right)
	{
		m_velocity.x += m_speed;
	}
}

void Ball::SetVelocity(const Position& _position)
{
	m_velocity = _position;
}
