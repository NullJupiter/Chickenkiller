#include "Enemy.h"

Enemy::Enemy(const glm::vec2& position, const glm::vec2& size)
	: Entity(position, size)
{
	mTexture = Asylum::ResourceManager::GetTexture("test-texture");

	mRotation = glm::radians(45.0f);
	mTint = { 200, 100, 255, 255 };
}

void Enemy::OnUpdate(float dt)
{
}

void Enemy::OnRender()
{
	Asylum::Renderer::DrawRectangle(mPosition, mSize, mTexture, mTint, mRotation);
}
