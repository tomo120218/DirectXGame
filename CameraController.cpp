#include "CameraController.h"
#include "Player.h"
using namespace KamataEngine;

void CameraController::Initialize() { camera_.Initialize(); }

void CameraController::Update() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	const Vector3& targetVelocity = target_->GetVelocity();

	cameraPosition_ = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

	camera_.translation_.x = Lerp(camera_.translation_.x, cameraPosition_.x, kInterpolationRate);

	camera_.translation_.x = max(camera_.translation_.x, camera_.translation_.x + targetMargin.left);
	camera_.translation_.x = min(camera_.translation_.x, camera_.translation_.x + targetMargin.right);
	camera_.translation_.y = max(camera_.translation_.y, camera_.translation_.y + targetMargin.bottom);
	camera_.translation_.y = min(camera_.translation_.y, camera_.translation_.y + targetMargin.top);

	camera_.translation_.x = max(camera_.translation_.x, movableArea_.left);
	camera_.translation_.x = min(camera_.translation_.x, movableArea_.right);
	camera_.translation_.y = max(camera_.translation_.y, movableArea_.bottom);
	camera_.translation_.y = min(camera_.translation_.y, movableArea_.top);

	camera_.UpdateMatrix();
}

void CameraController::Reset() {

	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}
