#include "Enemy.h"

Enemy::Enemy(const glm::vec2& position, const glm::vec2& size)
	: Entity(position, size)
{
	mTexture = Asylum::ResourceManager::GetTexture("test-texture");
}

void Enemy::OnUpdate(float dt)
{
}

void Enemy::OnRender()
{
	Asylum::Renderer::DrawTexturedRect(mPosition, mSize, mTexture);
}
