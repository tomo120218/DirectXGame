#pragma once
#include "CameraController.h"
#include "DeathParticles.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "skydome.h"
#include <vector>

using namespace KamataEngine;

// ゲームシーンクラス
class GameScene {
public:
	~GameScene();
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	void GenerateBlocks();

	// 02_10 16枚目 衝突判定と応答
	void CheckAllCollisions();

	// 02_12 26枚目	デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// 02_12 4枚目 ゲームのフェーズ（型）
	enum class Phase {
		kPlay,  // ゲームプレイ
		kDeath, // デス演出
	};

	// 02_12 4枚目 ゲームの現在フェーズ（変数）
	Phase phase_;

	// 02_12 9枚目
	void ChangePhase();

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	Sprite* sprite_ = nullptr;
	// 3Dモデル
	Model* model_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// カメラ
	Camera camera_;
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	// ここから02_01からの追加
	//  プレイヤー
	Player* player_ = nullptr;
	// プレイヤーモデル
	Model* player_model_ = nullptr;

	// ブロックモデル
	Model* block_model_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// 02_03 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	// 02_04 マップチップフィールド
	MapChipField* mapChipField_;

	// 02_06カメラ移動
	CameraController* CController_ = nullptr;

	// 02_09 10枚目 エネミークラス
	// Enemy* enemy_ = nullptr;//02_10で削除
	// 02_09 10枚目 エネミーモデル
	Model* enemy_model_ = nullptr;
	// 02_10 4枚目
	std::list<Enemy*> enemies_;

	// 02_11 15枚目
	DeathParticles* deathParticles_ = nullptr;

	// 02_11 16枚目
	Model* deathParticle_model_ = nullptr;

	// 02_12 26枚目
	bool finished_ = false;
};