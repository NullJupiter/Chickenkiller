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
		Texture(const char* textureFilePath);
		Texture(unsigned char* data, uint32_t width, uint32_t height, uint32_t channels);
		~Texture();

		inline int GetWidth() const { return mWidth; };
		inline int GetHeight() const { return mHeight; };
		inline uint32_t GetID() const { return mTextureID; };
	private:
		void CreateTexture(unsigned char* data, const std::string& textureFilePath = "Dynamically loaded texture!");
	};

}