#include "ampch.h"
#include "Animation.h"

namespace Asylum {
	
	Animation::Animation(std::shared_ptr<TextureAtlas> correspondingTextureAtlas, uint32_t animationRow, uint32_t frameCount, float frameTime)
		: mCorrespondingTextureAtlas(correspondingTextureAtlas), mAnimationRow(animationRow), mFrameCount(frameCount), mFrameTime(frameTime)
	{
		mCurrentFrame = 0;
		mTimeSinceLastFrame = 0.0f;

		mTextureSize = { mCorrespondingTextureAtlas->GetWidth(), mCorrespondingTextureAtlas->GetHeight() };
		
		uint32_t textureRows = mCorrespondingTextureAtlas->GetRowCount();
		uint32_t textureColumns = mCorrespondingTextureAtlas->GetColumnCount();

		mFrameSize.x = (float)mTextureSize.x / textureColumns;
		mFrameSize.y = (float)mTextureSize.y / textureRows;

		mCurrentTextureCoords.resize(4);

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