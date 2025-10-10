#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

#include <vector>

class MapChipField;

class Enemy;

// 自キャラ
class Player {

private:
	enum LRDirection {
		kRiget,
		kLeft,
	};

	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCenter // 要素数
	};

	struct CollisionMapInfo {
		bool ceiling = false;       // 天井衝突フラグ
		bool landing = false;       // 着地フラグ
		bool hitWall = false;       // 壁衝突フラグ
		KamataEngine::Vector3 move; // 移動量
	};

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	uint32_t textureHandle_ = 0u;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformPlayer_;

	KamataEngine::Vector3 velocity_ = {};

	// 移動
	static inline const float kAcceleration = 0.2f;

	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 0.1f;

	static inline const float kBlank = 0.1f;

	// 自機の回転
	LRDirection lrDirection_ = LRDirection::kRiget;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

	static inline const float kTimeTurn = 0.3f;

	// 着地状態フラグ
	bool onGround_ = true;

	// 重力加速度
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度
	static inline const float kLimitFallSpeed = 0.5f;
	// ジャンプ初速
	static inline const float kJumpAcceleration = 1.0f;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kAttenuationLanding = 0.0001f;
	static inline const float kAttenuationWall = 0.0001f;
	static inline const float kGroundSearchHeight = 0.1f;

public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw();
	// 1 移動入力
	void InputMove();
	// 2 移動量を加味して衝突判定する
	// 上方向
	void MapHitCheckUP(CollisionMapInfo& info);
	// 下方向
	void MapHitCheckDown(CollisionMapInfo& info);
	// 右方向
	void MapHitCheckRight(CollisionMapInfo& info);
	// 左方向
	void MapHitCheckLeft(CollisionMapInfo& info);
	// 3 判定結果を反映して移動させる
	void MapHitMove(const CollisionMapInfo& info);
	// 4 天井に接触している場合の処理
	void CheckMapCeiling(const CollisionMapInfo& info);
	// 5
	void HitWall(const CollisionMapInfo& info);
	// 6 接地状態の切り替え
	void CheckMapLanding(const CollisionMapInfo& info);
	// 7 旋回制御
	void AnimateTurn();
	// マップ衝突チェック
	void MapHitCheck(CollisionMapInfo& info);

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	KamataEngine::Vector3 GetWorldPosition();

	AABB GetAABB();

	void OnCollision(const Enemy* enemy);

	bool isDead_ = false;

	bool IsDead() const { return isDead_; }
};