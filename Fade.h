#pragma once
#include "MyMath.h"

using namespace KamataEngine;

class Fade {
public:
	enum class Status {
		None,
		FadeIn,
		FadeOut,
	};

	// 初期化
	void Initialize();
	~Fade();
	// 更新
	void Update();
	// 描画
	void Draw();

	void Start(Status status, float duration);

	void Stop();

	bool IsFinished() const;

private:
	uint32_t textureHandle_ = 0;
	KamataEngine::Sprite* sprite_ = nullptr;
	Status status_ = Status::None;

	float duration_ = 0.0f;

	float counter_ = 0.0f;
};
