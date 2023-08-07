#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) { 
	assert(model);
	model_ = model;

	worldTranform_.Initialize();
	worldTranform_.scale_ = {100.0f, 100.0f, 100.0f};
	worldTranform_.UpdateMatrix();
}

void Ground::Update() {

}

void Ground::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTranform_, viewProjection);
}