#include "Ball.h"


Ball::Ball(Position _position, Texture& _texture)
	: Collider(ColliderBox{ _position.x, _position.y, (float)_texture.GetWidth(), (float)_texture.GetHeight() }, Type::dynamicCollider),
	m_position(_position), m_texture(_texture)
{
	m_velocity = Position{ (float)m_speed, 0 };
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

int Ball::GetSpeed() const
{
	return m_speed;
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

void Ball::ResetPosition()
{
	m_position = Position{ GameManager::Get()->GetWindowWidth() / 2.0f, GameManager::Get()->GetWindowHeight() / 2.0f };
	m_velocity = Position{ (float)m_speed, 0 };
}

void Ball::Render()
{
	m_texture.Render((int)m_position.x, (int)m_position.y);
}

void Ball::SetVelocity(const Position& _position)
{
	m_velocity = _position;
}
