#include "ampch.h"
#include "Framebuffer.h"

namespace Asylum {

	Framebuffer::Framebuffer(const FramebufferSpecs& specs)
		: mSize({specs.Width, specs.Height})
	{
		// create framebuffer object
		glGenFramebuffers(1, &mFramebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

		// create framebuffer color attachment
		glGenTextures(1, &mColorAttachement);
		glBindTexture(GL_TEXTURE_2D, mColorAttachement);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mSize.x, mSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorAttachement, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG("[!] Framebuffer isn't complete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &mFramebuffer);
		glDeleteTextures(1, &mColorAttachement);
	}

	void Framebuffer::SetSize(const glm::vec2& size)
	{
		mSize = size;

		glBindTexture(GL_TEXTURE_2D, mColorAttachement);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mSize.x, mSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

}