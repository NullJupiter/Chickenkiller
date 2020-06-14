#pragma once

#include <stdint.h>

namespace Asylum {

	struct FramebufferSpecs
	{
		uint32_t Width, Height;
		
		FramebufferSpecs(uint32_t width, uint32_t height)
			: Width(width), Height(height)
		{};

		FramebufferSpecs(const glm::vec2& size)
			: Width(size.x), Height(size.y)
		{};
	};

	class Framebuffer
	{
	private:
		uint32_t mFramebuffer = 0;
		uint32_t mColorAttachement = 0;

		glm::vec2 mSize;
	public:
		Framebuffer(const FramebufferSpecs& specs);
		~Framebuffer();

		inline uint32_t GetFramebuffer() const { return mFramebuffer; };
		inline uint32_t GetColorAttachment() const { return mColorAttachement; };

		void SetSize(const glm::vec2& size);
	};

}