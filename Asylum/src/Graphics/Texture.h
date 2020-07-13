#pragma once

#include <iostream>

namespace Asylum {

	class Texture 
	{
	private:
		uint32_t mTextureID;

		int mWidth, mHeight;
		int mNrOfChannels;
	public:
		Texture(const char* textureFilePath, uint32_t colorFormat);
		~Texture();

		inline int GetWidth() const { return mWidth; };
		inline int GetHeight() const { return mHeight; };
		inline uint32_t GetID() const { return mTextureID; };
	};

	class AnimationSheet : public Texture
	{
	private:
		uint32_t mRowCount;
		uint32_t mColumnCount;
	public:
		AnimationSheet(const char* textureFilePath, uint32_t colorFormat, uint32_t rowCount, uint32_t columnCount)
			: Texture(textureFilePath, colorFormat), mRowCount(rowCount), mColumnCount(columnCount) {};
		~AnimationSheet() = default;

		inline uint32_t GetRowCount() const { return mRowCount; };
		inline uint32_t GetColumnCount() const { return mColumnCount; };
	};
}