#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	delete model_; 
	delete player_;
	delete enemy_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("player.png");
	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// 敵の生成
	enemy_ = new Enemy;
	// 敵の初期化
	//Vector3 position = {0, 0, 20};
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, {15, 0, 80}, {0, 0, -0.1f});
	
	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() 
{ 
	player_->Update();

	enemy_->Update();

	CheckAllCollision();

	// デバッグカメラのifdef
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}
	// カメラの処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
	#endif
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() {
	Vector3 posA, posB;

	float enemyBulletRadius = 0.5f;
	float playerBulletRadius = 0.5f;
	float playerRadius = 1.0f;
	float enemyRadius = 1.0f;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	#pragma region
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();

		Vector3 Distance = {
		    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
		    (posB.z - posA.z) * (posB.z - posA.z)};
		if (Distance.x + Distance.y + Distance.z <=
		    (playerRadius + enemyBulletRadius) * (playerRadius + enemyBulletRadius)) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region
	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPosition();

		Vector3 Distance = {
		    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
		    (posB.z - posA.z) * (posB.z - posA.z)};
		if (Distance.x + Distance.y + Distance.z <=
		    (enemyRadius + playerBulletRadius) * (enemyRadius + playerBulletRadius)) {
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 
	for (EnemyBullet* eBullet : enemyBullets) {

		posA = eBullet->GetWorldPosition();
		for (PlayerBullet* pbullet : playerBullets) {
			posB = pbullet->GetWorldPosition();

			Vector3 Distance = {
			    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
			    (posB.z - posA.z) * (posB.z - posA.z)};
			if (Distance.x + Distance.y + Distance.z <=
			    (enemyBulletRadius + playerBulletRadius) *
			        (enemyBulletRadius + playerBulletRadius)) {
				eBullet->OnCollision();
				pbullet->OnCollision();
			}
		}
	}
	#pragma endregion
}