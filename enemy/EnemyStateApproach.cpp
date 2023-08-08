#include "EnemyStateApproach.h"
#include "Enemy.h"

void EnemyStateApproach::Update(Enemy* enemy) {
	const Vector3 kCharacterSpeed = {0.0f, 0.0f, -0.5f};

	enemy->Move(kCharacterSpeed);

	if (enemy->GetPosition().z <= -20.0f) {
		stateNumber_ = 1;
	}
}