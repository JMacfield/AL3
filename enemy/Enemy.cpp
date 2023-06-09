#include "Enemy.h"
#include <cassert>
#include "CreatedMath.h"

Enemy::Enemy() {

}

Enemy::~Enemy() { 
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

	delete phase_;
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model);
	
	model_ = model;
	textureHandle_ = TextureManager::Load("enemy.png");

	phase_ = new EnemyApproach();
	phase_->Initialize(this);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() { 
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	phase_->Update();
	worldTransform_.UpdateMatrix();

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::ChangingState(EnemyState* newState) { 
	delete phase_;
	phase_ = newState;
	phase_->Initialize(this);
}

void Enemy::Move(Vector3 velocity) { 
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::Fire() { 
	Vector3 velocity = {0.0f, 0.0f, -1.0f};
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}