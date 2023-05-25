#include "EnemyState.h"

void EnemyApproach::Update(Enemy* enemy) { 
	enemy->Move(kCharacterApproachSpeed);

	if (enemy->GetPosition().z < 0.0f) {
		enemy->ChangingState(new EnemyLeave());
	}
}

void EnemyLeave::Update(Enemy* enemy) { 
	enemy->Move(kCharacterLeaveSpeed); 
}