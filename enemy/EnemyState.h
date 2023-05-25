#pragma once

#include "Enemy.h"

class Enemy;

class EnemyState {
public:
	virtual ~EnemyState(){};

	virtual void Update(Enemy* enemy) = 0;
};

class EnemyApproach : public EnemyState {
public:
	void Update(Enemy* enemy);
};

class EnemyLeave : public EnemyState {
public:
	void Update(Enemy* enemy);
};