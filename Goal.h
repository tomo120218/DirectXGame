#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Goal {
public:
	Goal() = default;

	// 初期化
	void Initialize(const Vector3& position, Model* model, Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

	// ゴール位置取得
	Vector3 GetPosition() const { return position_; }

	// プレイヤー到達判定
	bool IsPlayerReached(const Vector3& playerPos) const;

private:
	Vector3 position_ = {};
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
	WorldTransform worldTransform_;
};