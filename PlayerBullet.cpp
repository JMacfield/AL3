#include "PlayerBullet.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// テクスチャ読み込む
	textureHandle_ = TextureManager::Load("black.png");
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}
void PlayerBullet::Update() {
	//// ワールドトランスフォーの初期化
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}