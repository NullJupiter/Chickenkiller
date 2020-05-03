#include "Player.h"

Player::Player(const glm::vec2& position, const glm::vec2& size)
	: Entity(position, size)
{
	mWalkAnimation = Asylum::ResourceManager::GetAnimation("player-right");
}

void Player::OnUpdate(float dt)
{
	if (Asylum::Input::IsKeyPressed(AM_KEY_RIGHT))
	{
		mWalkAnimation->OnUpdate(dt);
		mPosition.x += 3.0f * dt;
	}
}

void Player::OnRender()
{
	Asylum::Renderer::DrawAnimatedRect(mPosition, mSize, mWalkAnimation);
}
