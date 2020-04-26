#pragma once

#include "Asylum.h"

class GameLayer : public Asylum::Layer
{
private:
	// camera
	Asylum::OrthographicCamera mCamera;

	// shader
	std::shared_ptr<Asylum::Shader> mDefaultShader;

	// textures
	std::shared_ptr<Asylum::Texture> mTestTexture;

	std::vector<std::shared_ptr<Asylum::Animation>> mTestAnimations;
public:
	GameLayer();

	void OnUpdate(float dt) override;

	void OnDetach() override;
	void OnAttach() override;
};