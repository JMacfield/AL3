#pragma once

#include "Enemy.h"

class Enemy;

class EnemyState {
public:
	virtual ~EnemyState(){};
	virtual void Update() = 0;
	virtual void Initialize(Enemy* enemy_) = 0;

protected:
	Enemy* enemy;
};

class EnemyApproach : public EnemyState {
public:
	void Update();
	void Initialize(Enemy* enemy_);
};

class EnemyLeave : public EnemyState {
public:
	void Update();
	void Initialize(Enemy* enemy_);
};