#pragma once

#include "Engine/Engine.h"

class GameLayer : public Engine::Layer
{
private:
	// camera
	Engine::OrthographicCamera mCamera;

	// shader
	std::shared_ptr<Engine::Shader> mDefaultShader;

	// textures
	std::shared_ptr<Engine::Texture> mTestTexture;

	std::vector<std::shared_ptr<Engine::Animation>> mTestAnimations;
public:
	GameLayer();

	void OnUpdate(float dt) override;

	void OnDetach() override;
	void OnAttach() override;
};