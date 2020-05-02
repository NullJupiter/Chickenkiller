#pragma once

#include "Asylum.h"

class GameLayer : public Asylum::Layer
{
private:
	// camera
	Asylum::Scope<Asylum::OrthographicCameraController> mCameraController;
public:
	GameLayer();

	void OnUpdate(float dt) override;

	void OnDetach() override;
	void OnAttach() override;
private:
	void OnKeyPressed(int keycode);
};