#include "ampch.h"
#include "Texture.h"

#include <stb_image.h>

namespace Asylum {

	Texture::Texture(const char* textureFilePath)
	{
		// generate texture
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		// set the texture wrapping/filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load the texture data
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(textureFilePath, &mWidth, &mHeight, &mNrOfChannels, 0);

		// check color formats
		uint32_t internalFormat = 0, dataFormat = 0;
		if (mNrOfChannels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (mNrOfChannels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		assert(internalFormat & dataFormat);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, dataFormat, GL_UNSIGNED_BYTE, data);
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

