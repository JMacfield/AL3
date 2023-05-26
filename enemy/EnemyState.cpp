#include "EnemyState.h"

void EnemyApproach::Update(Enemy* enemy) { 
	const Vector3 kCharacterApproachSpeed = {0.0f, 0.0f, -0.5f};

	enemy->Move(kCharacterApproachSpeed);

	if (enemy->GetPosition().z < 0.0f) {
		enemy->ChangingState(new EnemyLeave());
	}
}

void EnemyLeave::Update(Enemy* enemy) { 
	const Vector3 kCharacterLeaveSpeed = {-0.5f, 0.5f, 0.0f};

	enemy->Move(kCharacterLeaveSpeed); 
}