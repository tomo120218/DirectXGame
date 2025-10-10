#pragma once
#include "CameraController.h"
#include "DeathParticles.h"
#include "Enemy.h"
#include "Fade.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>

class GameScene {

	enum class Phase {
		kPlay,
		kDeath,
		kFadeIn,
		kFadeOut,
	};

	Phase phase_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera camera_;
	Player* player_ = nullptr;

	std::list<Enemy*> enemies_;

	int enemySpoon = 3;

	CameraController* cameraController_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	KamataEngine::Model* modelSkydome_ = nullptr;

	KamataEngine::Model* modelPlayer_ = nullptr;

	KamataEngine::Model* modelEnemy_ = nullptr;

	Skydome* skydome_ = nullptr;

	MapChipField* mapChipField_;
	void GenerateBlocks();
	void ChangePhase();

	DeathParticles* deathParticles_ = nullptr;

	KamataEngine::Model* modelDeath_ = nullptr;

private:
	uint32_t textureHandle_ = 0;
	KamataEngine::Model* modelBlock_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

public:
	// 初期化
	void Initialize();
	~GameScene();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 全ての当たり判定
	void CheckAllCollisions();

	// 終了
	bool finished_ = false;

	// デスフラグ
	bool IsFinished() const { return finished_; }

	Fade* fade_ = nullptr;
};
