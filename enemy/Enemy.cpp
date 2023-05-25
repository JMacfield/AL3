#include "Enemy.h"
#include <cassert>
#include "CreatedMath.h"

Enemy::Enemy() {

}

Enemy::~Enemy() { 
	delete phase_;
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model);
	
	model_ = model;
	textureHandle_ = TextureManager::Load("enemy.png");

	phase_ = new EnemyApproach();

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() { 
	phase_->Update(this);
	worldTransform_.UpdateMatrix();
}

void Enemy::ChangingState(EnemyState* newState) { 
	delete phase_;
	phase_ = newState;
}

void Enemy::Move(Vector3 speed) { 
	worldTransform_.translation_ = Add(worldTransform_.translation_, speed);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}