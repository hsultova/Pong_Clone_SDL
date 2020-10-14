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

	int leftA = m_box.x;
	int rightA = m_box.x + m_box.w;
	int topA = m_box.y;
	int bottomA = m_box.y + m_box.h;

	int leftB = _collider.m_box.x;
	int rightB = _collider.m_box.x + _collider.m_box.w;
	int topB = _collider.m_box.y;
	int bottomB = _collider.m_box.y + _collider.m_box.h;

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
