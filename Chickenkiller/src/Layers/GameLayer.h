#pragma once

#include "Asylum.h"

class GameLayer : public Asylum::Layer
{
private:
	// camera
	std::unique_ptr<Asylum::OrthographicCameraController> mCameraController;

	// shader
	std::shared_ptr<Asylum::Shader> mDefaultShader;

	// textures
	std::shared_ptr<Asylum::Texture> mTestTexture;
public:
	GameLayer();

	void OnUpdate(float dt) override;

	void OnDetach() override;
	void OnAttach() override;
};