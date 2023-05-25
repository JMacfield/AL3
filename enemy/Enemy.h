#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "EnemyState.h"

class EnemyState;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Move(Vector3 speed);

	void ChangingState(EnemyState* newState);

	Vector3 GetPosition() { return worldTransform_.translation_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	EnemyState* phase_ = nullptr;
};

