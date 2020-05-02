#pragma once

#include <Asylum.h>

class Player : public Asylum::Entity
{
private:
	std::shared_ptr<Asylum::Animation> mWalkAnimation;
public:
	Player(const glm::vec2& position, const glm::vec2& size);

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() override;
};