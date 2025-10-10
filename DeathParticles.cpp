#include "DeathParticles.h"
#include "MapChipField.h"
#include "MyMath.h"
#include "cassert"
#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

void DeathParticles::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) {
		assert(model);
		model_ = model;
		worldTransform.Initialize();
		worldTransform.translation_ = position;
		camera_ = camera;
	}
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void DeathParticles::Update() {
	if (IsFinished()) {
		return;
	}
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
		worldTransform.TransferMatrix();
	}
	for (uint32_t i = 0; i < kNumParticles; ++i) {
		KamataEngine::Vector3 velocity = {kSpeed, 0, 0};

		float angle = kAngleUnit * i;

		KamataEngine::Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);

		velocity = Transform(velocity, matrixRotation);

		worldTransforms_[i].translation_ += velocity;
	}
	counter_ += 1.0f / 60.0f;
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		finished_ = true;
	}
	color_.w = std::clamp((1.0f - counter_ / kDuration), 0.0f, 1.0f);
	objectColor_.SetColor(color_);
}

void DeathParticles::Draw() {
	if (IsFinished()) {
		return;
	}
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objectColor_);
	}
}
