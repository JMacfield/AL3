#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "EnemyState.h"
#include "CreatedMath.h"
#include "EnemyBullet.h"

class Player;

class EnemyState;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void Move(Vector3 velocity);
	void Fire();
	void ChangingState(EnemyState* newState);

	Vector3 GetPosition() { return worldTransform_.translation_; }
	Vector3 GetSpeed() { return velocity_; }
	void SetPosition(const Vector3& position) { worldTransform_.translation_ = position; }

	static const int kFireInterval = 60;
	int32_t fireTimer;

	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	EnemyState* phase_ = nullptr;
	
	std::list<EnemyBullet*> bullets_;

	Player* player_ = nullptr;
};

