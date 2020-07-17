#include "ampch.h"
#include "Animation.h"

namespace Asylum {
	
	Animation::Animation(uint32_t animationSheetID, const glm::vec2& animationSheetSize, float rowCount, float columnCount, uint32_t animationRow, uint32_t frameCount, float frameTime)
		: mAnimationSheetID(animationSheetID), mTextureSize(animationSheetSize), mAnimationRow(animationRow), mFrameCount(frameCount), mFrameTime(frameTime)
	{
		mCurrentFrame = 0;
		mTimeSinceLastFrame = 0.0f;

		mFrameSize.x = (float)mTextureSize.x / columnCount;
		mFrameSize.y = (float)mTextureSize.y / rowCount;

		UpdateTextureCoords();
	}
	
	void Animation::OnUpdate(float dt)
	{
		mTimeSinceLastFrame += dt;
		if (mTimeSinceLastFrame >= mFrameTime)
		{
			mCurrentFrame++;
			if (mCurrentFrame >= mFrameCount)
			{
				mCurrentFrame = 0;
			}

			UpdateTextureCoords();
			mTimeSinceLastFrame = 0.0f;
		}
	}

	void Animation::UpdateTextureCoords()
	{
		static glm::vec2 framePercentage = { mFrameSize.x / mTextureSize.x, mFrameSize.y / mTextureSize.y };

		mCurrentTextureCoords[0] = { mCurrentFrame * framePercentage.x, (1 - (mAnimationRow - 1) * framePercentage.y) - framePercentage.y };
		mCurrentTextureCoords[1] = { (mCurrentFrame * framePercentage.x) + framePercentage.x, (1 - (mAnimationRow - 1) * framePercentage.y) - framePercentage.y};
		mCurrentTextureCoords[2] = { (mCurrentFrame * framePercentage.x) + framePercentage.x, (1 - (mAnimationRow - 1) * framePercentage.y) };
		mCurrentTextureCoords[3] = { mCurrentFrame * framePercentage.x, (1 - (mAnimationRow - 1) * framePercentage.y) };
	}

}