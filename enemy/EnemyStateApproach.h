#pragma once

#include "EnemyState.h"

class EnemyStateApproach : public EnemyState {
public:
	void Update(Enemy* enemy) override;
};