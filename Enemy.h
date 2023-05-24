#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Enemy {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	private:
		enum class Phase {
			Approach,
			Leave,
	};

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	Phase phase_ = Phase::Approach;

	void Approach();
	void Leave();
};