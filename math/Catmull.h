#pragma once

#include "CreatedMath.h"
#include <vector>
#include <PrimitiveDrawer.h>
#include "ViewProjection.h"

class Catmull {
public:
	void Initialize(const ViewProjection& view);

	void Update();

	void Draw();

private:
	std::vector<Vector3> controlPoints_;
	PrimitiveDrawer* primitiveDrawer_;
	std::vector<Vector3> drawingPoints_;

	size_t pointCounts_;
	Vector3 CatmullRom(std::vector<Vector3> points, float t);
};