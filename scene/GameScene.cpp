#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 敵
	enemy_ = std::make_unique<Enemy>();
	enemyModel_.reset(Model::CreateFromOBJ("Enemy", true));

	std::vector<Model*> enemyModels = {enemyModel_.get()};
	enemy_->Initialize(enemyModels);

	// 自キャラの生成
	player_ = std::make_unique<Player>();

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), 
		modelFighterL_arm_.get(), modelFighterR_arm_.get()};

	player_->Initialize(playerModels);

	// 天球
	skyDome_ = std::make_unique<SkyDome>();
	skyDomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	skyDome_->Initialize(skyDomeModel_.get(), {0, 0, 0});

	// 地面
	ground_ = std::make_unique<Ground>();
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Initialize(groundModel_.get(), {0, 0, 0});

	// デバッグカメラ
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	// カメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());

	player_->SetViewProjection(&followCamera_->GetViewProjection());
}

void GameScene::Update() 
{ 
	player_->Update();
	enemy_->Update();
	skyDome_->Update();
	ground_->Update();

	viewProjection_.UpdateMatrix();
	followCamera_->Update();

	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

	/*#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if(input_->TriggerKey(DIK_0)&&isDebugCameraActive_ == true){
		isDebugCameraActive_ = false;
	}

	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
	#endif*/

	ImGui::Begin("Debug Window");
	ImGui::Text("Debug Camera Toggle : 0");
	ImGui::End();

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
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
	skyDome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

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
