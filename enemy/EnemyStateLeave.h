#pragma once

#include "EnemyState.h"

class EnemyStateLeave : public EnemyState {
public:
	void Update(Enemy* enemy) override;
};