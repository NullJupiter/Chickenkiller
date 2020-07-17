#pragma once

#include <array>

#include <glm/glm.hpp>
#include "Graphics/Texture.h"

namespace Asylum {

	class Animation
	{
	private:
		uint32_t mAnimationSheetID;

		uint32_t mAnimationRow;

		std::array<glm::vec2, 4> mCurrentTextureCoords;

		uint32_t mCurrentFrame;
		uint32_t mFrameCount;
		
		float mTimeSinceLastFrame;
		float mFrameTime;

		glm::vec2 mTextureSize;
		glm::vec2 mFrameSize;
	public:
		Animation(uint32_t animationSheetID, const glm::vec2& animationSheetSize, float rowCount, float columnCount, uint32_t animationRow, uint32_t frameCount, float frameTime);
		~Animation() = default;

		void OnUpdate(float dt);

		// getter
		inline const std::array<glm::vec2, 4>& GetCurrentTextureCoords() const { return mCurrentTextureCoords; };
		inline uint32_t GetAnimationSheetID() const { return mAnimationSheetID; };
	private:
		void UpdateTextureCoords();
	};

	class AnimationSheet : public Texture
	{
	private:
		uint32_t mRowCount;
		uint32_t mColumnCount;

		std::unordered_map<std::string, Ref<Animation>> mAnimations;
	public:
		AnimationSheet(const char* textureFilePath, uint32_t rowCount, uint32_t columnCount)
			: Texture(textureFilePath), mRowCount(rowCount), mColumnCount(columnCount) {};
		~AnimationSheet() = default;

		inline uint32_t GetRowCount() const { return mRowCount; };
		inline uint32_t GetColumnCount() const { return mColumnCount; };

		inline const std::unordered_map<std::string, Ref<Animation>>& GetAnimations() const { return mAnimations; };
		inline const Ref<Animation>& GetAnimation(const std::string& name) { return mAnimations[name]; };

		void AddNewAnimation(const std::string& name, uint32_t animationRow, uint32_t frameCount, float frameTime) 
		{
			mAnimations[name] = CreateRef<Animation>(GetID(), glm::vec2((float)GetWidth(), (float)GetHeight()), mRowCount, mColumnCount, animationRow, frameCount, frameTime); 
		}
	};

}