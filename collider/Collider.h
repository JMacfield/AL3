#pragma once

#include "Vector3.h"

class Collider {
public:
	float GetRadius() const { return radius_; }
	float SetRadius(float rad) { radius_ = rad; }
	virtual ~Collider() {}
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() = 0;

private:
	float radius_ = 1.0f;
};