#pragma once

#include <Asylum.h>

class Enemy : public Asylum::Entity
{
private:
	Asylum::Ref<Asylum::Texture> mTexture;
public:
	Enemy(const glm::vec2& position, const glm::vec2& size);

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() override;
};