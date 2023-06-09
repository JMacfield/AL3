#include "EnemyState.h"

void EnemyApproach::Update() { 
	if (--enemy->fireTimer <= 0) {
		enemy->Fire();
		enemy->fireTimer = enemy->kFireInterval;
	}

	const Vector3 kCharacterApproachSpeed = {0.0f, 0.0f, -0.2f};

	enemy->Move(kCharacterApproachSpeed);

	if (enemy->GetPosition().z < 0.0f) {
		enemy->ChangingState(new EnemyLeave());
	}
}

void EnemyApproach::Initialize(Enemy* enemy_) { 
	enemy = enemy_;
	enemy->fireTimer = enemy->kFireInterval;
}

void EnemyLeave::Update() { 
	const Vector3 kCharacterLeaveSpeed = {-0.2f, 0.2f, 0.0f};

	enemy->Move(kCharacterLeaveSpeed); 
}

void EnemyLeave::Initialize(Enemy* enemy_) { enemy = enemy_; }