#include "Player.h"
#include "MyMath.h"
#include <Input.h>
#include <Xinput.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

void Player::Initialize(const std::vector<Model*>&models) { 
	BaseCharacter::Initialize(models);

	models_[kModelIndexBody] = models[kModelIndexBody];
	models_[kModelIndexHead] = models[kModelIndexHead];
	models_[kModelIndexL_arm] = models[kModelIndexL_arm];
	models_[kModelIndexR_arm] = models[kModelIndexR_arm];

	worldTransformL_arm_.translation_.x = -1.5f;
	worldTransformR_arm_.translation_.x = 1.5f;
	worldTransformL_arm_.translation_.y = 5.0f;
	worldTransformR_arm_.translation_.y = 5.0f;

	SetParent(&GetWorldTransformBody());
	worldTransformBody_.parent_ = worldTransform_.parent_;

	InitializeFloatingGimmick();

	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
}

void Player::Update() { 
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float speed = 0.3f;

		Vector3 move {
			(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
			(float)joyState.Gamepad.sThumbLY / SHRT_MAX
		};

		move = Multiply(speed, Normalize(move));

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);

		move = TransformNormal(move, rotateMatrix);

		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);
		worldTransformBody_.translation_ = worldTransformBase_.translation_;

		worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody_.rotation_.y = worldTransformBase_.rotation_.y;
	}

	UpdateFloatingGimmick();

	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {
	models_[kModelIndexBody]->Draw(worldTransformBody_, viewProjection);
	models_[kModelIndexHead]->Draw(worldTransformHead_, viewProjection);
	models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
	models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);
}

Vector3 Player::GetWorldPosition() { 
	Vector3 worldPosition;

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];

	return worldPosition;
}

void Player::SetParent(const WorldTransform* parent) { 
	worldTransformHead_.parent_ = parent;
	worldTransformL_arm_.parent_ = parent;
	worldTransformR_arm_.parent_ = parent;
}

void Player::InitializeFloatingGimmick() {
	for (int i = 0; i < kMaxMoveModelParts_; i++) {
		floatingParameter_[i] = 0.0f;
	}
}

void Player::UpdateFloatingGimmick() {
	uint16_t floatingCycle[2]{};
	floatingCycle[0] = 120;
	floatingCycle[1] = 120;

	float steps[2]{};

	for (int i = 0; i < kMaxMoveModelParts_; i++) {
		steps[i] = 2.0f * (float)M_PI / floatingCycle[i];
		floatingParameter_[i] += steps[i];
		floatingParameter_[i] = (float)std::fmod(floatingParameter_[i], 2.0f * M_PI);
	}

	const float floatingAmplitude = 0.5f;

	worldTransformBody_.translation_.y = std::sin(floatingParameter_[0]) * floatingAmplitude;

	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_[1]) * 0.75f;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_[1]) * 0.75f;
}