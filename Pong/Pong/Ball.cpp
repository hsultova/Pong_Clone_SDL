#include "Ball.h"


Ball::Ball(Texture& _texture) :m_texture(_texture)
{
	m_position = Position{ 0, 0 };
	m_velocity = Position{ 0, 0 };
}

Ball::~Ball()
{
}

void Ball::Update()
{
}

void Ball::Move()
{
}

void Ball::Render()
{
	m_texture.Render(GameManager::Get()->GetWindowWidth() / 2, GameManager::Get()->GetWindowHeight() / 2);
}
