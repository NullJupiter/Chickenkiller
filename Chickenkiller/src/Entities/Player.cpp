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

	mAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-up"));
	mAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-down"));
	mAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-left"));
	mAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-right"));

	mCurrentAnimation = mAnimations[Animations::PlayerDown];
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
