#pragma once

#include <glm/glm.hpp>

#include "Core/Layer.h"
#include "Graphics/OrthographicCameraController.h"

namespace Asylum {

	class EditorLayer : public Layer
	{
	private:
		bool mIsGameRunning;
		glm::vec2 mGameWindowSize;

		Scope<OrthographicCameraController> mCameraController;
	public:
		EditorLayer() {};

		virtual void OnUpdate(float dt) override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
	};

}