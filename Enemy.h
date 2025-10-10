#pragma once

#include "KamataEngine.h"
#include "MyMath.h"

#include <vector>

class Player;

class Enemy {
private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	uint32_t textureHandle_ = 0u;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformEnemy_;

	KamataEngine::Vector3 velocity_ = {};

	// 敵の移動速度
	static inline const float kWalkSpeed = 0.05f;
	// 最初の角度[度]
	static inline const float kWalkMotionAngleStart = 1.0f;
	// 最後の角度[度]
	static inline const float kWalkMotionAngleEnd = 1.0f;
	// アニメーションの周期となる時間
	static inline const float kWalkMotionTime = 1.0f;
	// 経過時間
	float walkTimer_ = 0.0f;

public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw();

	KamataEngine::Vector3 GetWorldPosition();

	AABB GetAABB();

	void OnCollision(const Player* player);
};
