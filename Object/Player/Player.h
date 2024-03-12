#pragma once

#include "Collision/Collider.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include <optional>

class GameScene;

class Player : public Collider {
public:
	Player();
	~Player();

	void Initialize(
	    Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm,
	    Model* modelWeapon, Model* modelBullet);

	void Update();

	void DrawUI();
	void Draw(ViewProjection& viewProjection);

	bool UnCollision() override;
	bool OnCollision() override;

	Vector3 GetWorldPosition() override;
	WorldTransform GetRightArm() { return worldTransformR_arm_; }

	void Attack();
	void Melee();

	void InitializeFloatingGimmick();
	void UpdateFloatingGimmick();

	void BehaviorRootUpdate();
	void BehaviorRootInitialize();

	void Create3DReticle();
	void Create2DReticle(const ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
	const WorldTransform& GetWorldTransformBase() { return worldTransformBase_; }
	Vector3 GetWorld3DReticlePosition();

	void SetWorldPosition(Vector3 prePosition);
	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	void SetParent(const WorldTransform* parent);

	int GetHP() { return lifePoint_; }

private:
	enum class Behavior { kRoot };
	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformWeapon_;
	WorldTransform worldTransformSword_;

	WorldTransform worldTransformKnife_;

	WorldTransform worldTransform3DReticle_;

	const ViewProjection* viewProjection_ = nullptr;

	Model* modelBody_;
	Model* modelHead_;
	Model* modelL_arm_;
	Model* modelR_arm_;
	Model* modelWeapon_;
	Model* modelBullet_;

	std::unique_ptr<Model> modelSword_;

	float bulletImpactPoint_;
	float floatingParameter_ = 0.0f;

	Sprite* sprite2DReticle_ = nullptr;
	uint32_t reticleTexture_ = 0u;
	Matrix4x4 matViewPort_;

	GameScene* gameScene_;

	bool isDead_ = true;

	Vector2 spritePosition_;

	bool isBullet_;
	
	Input* input_;

	Vector3 velocity_;

	Sprite* life1 = nullptr;
	Sprite* life2 = nullptr;
	Sprite* life3 = nullptr;
	Sprite* life4 = nullptr;
	Sprite* life5 = nullptr;

	uint32_t life1Texture = 0u;
	uint32_t life2Texture = 0u;
	uint32_t life3Texture = 0u;
	uint32_t life4Texture = 0u;
	uint32_t life5Texture = 0u;

	int lifePoint_ = 5;

	Sprite* knife0 = nullptr;
	Sprite* knife1 = nullptr;
	Sprite* knife2 = nullptr;
	Sprite* knife3 = nullptr;
	Sprite* knife4 = nullptr;
	Sprite* knife5 = nullptr;
	Sprite* knife6 = nullptr;
	Sprite* knife7 = nullptr;
	Sprite* knife8 = nullptr;
	Sprite* knife9 = nullptr;
	Sprite* knife10 = nullptr;
	
	uint32_t knife0Texture = 0u;
	uint32_t knife1Texture = 0u;
	uint32_t knife2Texture = 0u;
	uint32_t knife3Texture = 0u;
	uint32_t knife4Texture = 0u;
	uint32_t knife5Texture = 0u;
	uint32_t knife6Texture = 0u;
	uint32_t knife7Texture = 0u;
	uint32_t knife8Texture = 0u;
	uint32_t knife9Texture = 0u;
	uint32_t knife10Texture = 0u;

	Sprite* knifeThrow = nullptr;
	uint32_t knifeThrowTexture = 0u;

	int knifeCount_ = 10;
	int knifeTimeCount_ = 0;

	Sprite* attackSign = nullptr;
	uint32_t attackSignTexture = 0u;

	bool isKnifeTimerStart = false;

	int comboCount = 0;
	int comboBeha = 0;

	bool isRBPush = true;
};