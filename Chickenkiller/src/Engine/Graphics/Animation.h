#pragma once

#include <glm/glm.hpp>
#include "Engine/Graphics/Texture.h"

namespace Engine {

	class Animation
	{
	private:
		std::shared_ptr<TextureAtlas> mCorrespondingTextureAtlas;
		uint32_t mAnimationRow;


		std::vector<glm::vec2> mCurrentTextureCoords;

		uint32_t mCurrentFrame;
		uint32_t mFrameCount;
		
		float mTimeSinceLastFrame;
		float mFrameTime;

		glm::vec2 mTextureSize;
		glm::vec2 mFrameSize;
	public:
		Animation(std::shared_ptr<TextureAtlas> correspondingTextureAtlas, uint32_t animationRow, uint32_t frameCount, float frameTime);
		~Animation() = default;

		void OnUpdate(float dt);

		// getter
		inline uint32_t GetTextureID() const { return mCorrespondingTextureAtlas->GetID(); };
		inline const std::vector<glm::vec2>& GetCurrentTextureCoords() const { return mCurrentTextureCoords; };
	private:
		void UpdateTextureCoords();
	};

}