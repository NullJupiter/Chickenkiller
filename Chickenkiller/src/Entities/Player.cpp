#include "Player.h"

enum Animations
{
	PlayerUp,
	PlayerDown,
	PlayerLeft,
	PlayerRight
};

Player::Player(const glm::vec2& position, const glm::vec2& size)
	: Entity(position, size)
{
	mSpeed = 3.0f;

	const Asylum::Ref<Asylum::AnimationSheet>& animationSheet = Asylum::ResourceManager::GetAnimationSheet("player-animation-sheet");
	mAnimations.push_back(animationSheet->GetAnimation("player-up"));
	mAnimations.push_back(animationSheet->GetAnimation("player-down"));
	mAnimations.push_back(animationSheet->GetAnimation("player-left"));
	mAnimations.push_back(animationSheet->GetAnimation("player-right"));

	mCurrentAnimation = mAnimations[Animations::PlayerDown];

	Asylum::OrthographicCameraController* cameraController = Asylum::OrthographicCameraController::Get();
	cameraController->SetMinZoomLevel(5.0f);
	cameraController->SetMaxZoomLevel(7.0f);
}

void Player::OnUpdate(float dt)
{
	// update movement
	if (Asylum::Input::IsKeyPressed(AM_KEY_W))
	{
		mCurrentAnimation = mAnimations[Animations::PlayerUp];
		mCurrentAnimation->OnUpdate(dt);
		mPosition.y += mSpeed * dt;
	}
	if (Asylum::Input::IsKeyPressed(AM_KEY_S))
	{
		mCurrentAnimation = mAnimations[Animations::PlayerDown];
		mCurrentAnimation->OnUpdate(dt);
		mPosition.y -= mSpeed * dt;
	}
	if (Asylum::Input::IsKeyPressed(AM_KEY_A))
	{
		mCurrentAnimation = mAnimations[Animations::PlayerLeft];
		mCurrentAnimation->OnUpdate(dt);
		mPosition.x -= mSpeed * dt;
	}
	if (Asylum::Input::IsKeyPressed(AM_KEY_D))
	{
		mCurrentAnimation = mAnimations[Animations::PlayerRight];
		mCurrentAnimation->OnUpdate(dt);
		mPosition.x += mSpeed * dt;
	}

	// update camera position
	Asylum::OrthographicCameraController::Get()->SetCameraPosition(mPosition);
}

void Player::OnRender()
{
	Asylum::Renderer::DrawRectangle(mPosition, mSize, mCurrentAnimation, mTint, mRotation);
}
