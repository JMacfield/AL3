#include "Enemy.h"
#include <cassert>
#include "CreatedMath.h"

Enemy::Enemy() {

}

Enemy::~Enemy() { 
	
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	textureHandle_ = TextureManager::Load("enemy.png");
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;
	stateArray_[0] = new EnemyStateApproach();
	stateArray_[1] = new EnemyStateLeave();
}

void Enemy::Update() { 
	worldTransform_.UpdateMatrix();

	previousStateNumber_ = stateNumber_;
	stateNumber_ = stateArray_[stateNumber_]->GetNumber();
	stateArray_[stateNumber_]->Update(this);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move(Vector3 speed) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, speed);
}