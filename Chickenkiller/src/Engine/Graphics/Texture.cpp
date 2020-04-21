#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace Engine {

	Texture::Texture(const char* textureFilePath, uint32_t colorFormat)
	{
		// generate texture
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		// set the texture wrapping/filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load the texture
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(textureFilePath, &mWidth, &mHeight, &mNrOfChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, colorFormat, GL_UNSIGNED_BYTE, data);
		}
		else {
			LOG("Could not load texture! (filepath: " << textureFilePath << ")");
		}

		// cleanup
		stbi_image_free(data);
	}

	Texture::~Texture() 
	{
		glDeleteTextures(1, &mTextureID);
	}

}

