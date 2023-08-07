#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include <memory>

class Ground {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTranform_;
	Model* model_ = nullptr;
};