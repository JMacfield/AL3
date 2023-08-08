#pragma once

class Enemy;

class EnemyState {
public:
	virtual void Update(Enemy* enemy) = 0;

	int GetNumber() { return stateNumber_; }

protected:
	static int stateNumber_;
};