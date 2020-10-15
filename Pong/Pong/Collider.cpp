#include "Collider.h"

Collider::Collider(ColliderBox _box, Type _type)
	:m_box(_box), m_type(_type)
{
}

Collider::~Collider()
{
}

bool Collider::Collide(const Collider& _collider)
{
	if (m_type == Type::staticCollider && _collider.m_type == Type::staticCollider)
	{
		return false;
	}

	float leftA = m_box.x;
	float rightA = m_box.x + m_box.w;
	float topA = m_box.y;
	float bottomA = m_box.y + m_box.h;

	float leftB = _collider.m_box.x;
	float rightB = _collider.m_box.x + _collider.m_box.w;
	float topB = _collider.m_box.y;
	float bottomB = _collider.m_box.y + _collider.m_box.h;

	if (leftA >= rightB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (bottomA <= topB)
	{
		return false;
	}

	return true;
}

void Collider::UpdateCollisionBox(float _x, float _y)
{
	m_box.x = _x;
	m_box.y = _y;
}
