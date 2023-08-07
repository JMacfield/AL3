#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model) { 
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.UpdateMatrix();
}

void Player::Update() { 
	
}

void Player::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection);
}