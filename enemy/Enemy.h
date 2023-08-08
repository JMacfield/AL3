#pragma once

#include "EnemyState.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"

#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"

class EnemyState;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	Vector3 GetPosition() { return worldTransform_.translation_; }
	Vector3 GetSpeed() { return velocity_; }

	void SetPosition(const Vector3& position) { worldTransform_.translation_ = position; }
	void Move(Vector3 velocity);

private:
	WorldTransform worldTransform_;
	Model* model_;

	uint32_t textureHandle_;
	Vector3 velocity_;

	int stateNumber_;
	int previousStateNumber_;

	EnemyState* stateArray_[2];
};