#pragma once

#include <array>

#include <glm/glm.hpp>
#include "Graphics/Texture.h"

namespace Asylum {

	class Animation
	{
	private:
		Ref<AnimationSheet> mCorrespondingAnimationSheet;
		uint32_t mAnimationRow;


		std::array<glm::vec2, 4> mCurrentTextureCoords;

		uint32_t mCurrentFrame;
		uint32_t mFrameCount;
		
		float mTimeSinceLastFrame;
		float mFrameTime;

		glm::vec2 mTextureSize;
		glm::vec2 mFrameSize;
	public:
		Animation(const Ref<AnimationSheet>& correspondingAnimationSheet, uint32_t animationRow, uint32_t frameCount, float frameTime);
		~Animation() = default;

		void OnUpdate(float dt);

		// getter
		inline uint32_t GetTextureID() const { return mCorrespondingAnimationSheet->GetID(); };
		inline const std::array<glm::vec2, 4>& GetCurrentTextureCoords() const { return mCurrentTextureCoords; };
	private:
		void UpdateTextureCoords();
	};

}