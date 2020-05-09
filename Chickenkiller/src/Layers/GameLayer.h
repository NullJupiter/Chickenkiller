#pragma once

#include "Asylum.h"

class GameLayer : public Asylum::Layer
{
public:
	GameLayer();

	void OnUpdate(float dt) override;

	void OnDetach() override;
	void OnAttach() override;

	void AddEventCallbacks() override;
private:
	void OnKeyPressed(int keycode);
};