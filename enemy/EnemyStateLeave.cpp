#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Update(Enemy* enemy) {
	const Vector3 kCharacterSpeed = {-0.5f, 0.5f, 0.0f};

	enemy->Move(kCharacterSpeed);
}