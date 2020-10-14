#pragma once

enum class Type
{
	staticCollider,
	dynamicCollider
};

struct ColliderBox
{
	float x;
	float y;
	float w;
	float h;
};

class Collider
{
public:
	Collider(ColliderBox _box, Type _type);
	~Collider();

	bool Collide(const Collider& _collider);
	void UpdateCollisionBox(float _x, float _y);

private:
	ColliderBox m_box;
	Type m_type;
};

