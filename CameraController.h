#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

class Player;

class CameraController {

public:
	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	Vector3 targetOffset_ = {0, 0, -15.0f};

	Rect movableArea_ = {0, 100, 0, 100};

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	void SetMovableArea(Rect area) { movableArea_ = area; }

	const KamataEngine::Camera& GetViewProjection() const { return camera_; }

private:
	KamataEngine::Camera camera_;

	KamataEngine::Vector3 cameraPosition_;

	static inline const float kInterpolationRate = 0.05f;

	static inline const float kVelocityBias = 30.0f;

	static inline const Rect targetMargin = {-9.0f, 9.0f, -5.0f, 5.0f};

	Player* target_ = nullptr;
};
