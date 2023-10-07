#include "Player.h"
#include "MyMath.h"
#include <Input.h>
#include <Xinput.h>
#include <cassert>

// 弧度法変換
#ifndef M_PI
#define M_PI 3.14
#endif

// 変換
#define deg_to_rad(deg) (deg * (M_PI/180))

void Player::Initialize(Model* model) { 
	assert(model);
	model_ = model;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();
}

void Player::Update() { 
	// プレイヤーの挙動はMove関数にまとまってる
	Move();

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection);
}

void Player::Move() {
	Vector3 move = {0, 0, 0};

	float speed = 1.0f;
	float angle;
	float rad;

	// 左方向へ移動（現在３０°程度）
	if (input_->PushKey(DIK_A)) {
		angle = 215.0f;
		rad = (float)angle * (float)deg_to_rad(angle);
		Vector3 direction = {cosf(rad), sinf(rad), 0};
		move = direction * speed;
	}

	// 右方向へ移動（現在３０°程度）
	if (input_->PushKey(DIK_D)) {
		angle = 260.0f;
		rad = (float)angle * (float)deg_to_rad(angle);
		Vector3 direction = {cosf(rad), sinf(rad), 0};
		move = direction * -speed;
	}

	// 

	if (input_->PushKey(DIK_SPACE)) {
		worldTransform_.translation_.y -= 10.0f;
	}

	// 常に下へ自由落下
	worldTransform_.translation_.y -= 0.2f;

	// 更新した座標を追加計算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
}

Vector3 Player::GetWorldPosition() { 
	Vector3 worldPosition;

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];

	return worldPosition;
}

