#include "Player.h"
#include "MyMath.h"
#include <Input.h>
#include <Xinput.h>
#include <cassert>

void Player::Initialize(Model* model) { 
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	//worldTransform_.scale_ = {0.0f, 0.0f, 0.0f};
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

		worldTransform_.translation_ = Add(worldTransform_.translation_, move);
		worldTransform_.rotation_.y = std::atan2(move.x, move.z);
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Player::GetWorldPosition() { 
	Vector3 worldPosition;

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];

	return worldPosition;
}

