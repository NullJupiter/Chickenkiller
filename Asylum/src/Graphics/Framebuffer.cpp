#include "ampch.h"
#include "Framebuffer.h"

namespace Asylum {

	Framebuffer::Framebuffer(const FramebufferSpecs& specs)
		: mSpecification(specs)
	{
		Init();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &mFramebuffer);
		glDeleteTextures(1, &mColorAttachement);
	}

	void Framebuffer::Init()
	{
		if (mFramebuffer)
		{
			glDeleteFramebuffers(1, &mFramebuffer);
			glDeleteTextures(1, &mColorAttachement);
		}

		// create framebuffer object
		glGenFramebuffers(1, &mFramebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

		// create framebuffer color attachment
		glGenTextures(1, &mColorAttachement);
		glBindTexture(GL_TEXTURE_2D, mColorAttachement);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSpecification.Width, mSpecification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorAttachement, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG("[!] Framebuffer isn't complete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height)
	{
		mSpecification.Width = width;
		mSpecification.Height = height;
	
		Init();
	}


}