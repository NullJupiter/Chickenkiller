#pragma once

#include <glm/glm.hpp>
#include "Graphics/Shader.h"
#include "Graphics/Animation.h"

namespace Asylum {

	struct VertexData
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexSlot;
	};

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void DrawToFramebuffer(bool useFramebuffer);
		static uint32_t GetFramebufferRender();

		// draw cicle
		static void BeginDraw();
		static void EndDraw();

		// colored rect draw calls
		static void DrawColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float zDepth);
		
		// rotated colored rect draw calls
		static void DrawRotatedColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angle);
		static void DrawRotatedColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angle, float zDepth);

		// textured rect draw calls
		static void DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture);
		static void DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth);
		static void DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, const glm::vec3& tint);
		static void DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth, const glm::vec3& tint);

		// rotated and textured rect draw calls
		static void DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle);
		static void DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle, float zDepth);
		static void DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle, const glm::vec3& tint);
		static void DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle, float zDepth, const glm::vec3& tint);

		// animated rect draw calls
		static void DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, Ref<Animation> animation);
		static void DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, float zDepth, Ref<Animation> animation);
		static void DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& tint, Ref<Animation> animation);
		static void DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& tint, float zDepth, Ref<Animation> animation);

		// rotated animated rect draw calls
		static void DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, Ref<Animation> animation);
		static void DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& tint, Ref<Animation> animation);
		static void DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, float zDepth, Ref<Animation> animation);
		static void DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& tint, float zDepth, Ref<Animation> animation);
	private:
		static void Flush();
		
		// implementations
		static void DrawColoredRectImpl(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float zDepth);
		static void DrawRotatedColoredRectImpl(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float zDepth, float angle);

		static void DrawTexturedRectImpl(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth, const glm::vec3& tint);
		static void DrawRotatedTexturedRectImpl(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth, const glm::vec3& tint, float angle);

		static void DrawAnimatedRectImpl(const glm::vec2& position, const glm::vec2& size, float zDepth, const glm::vec3& tint, Ref<Animation> animation);
		static void DrawRotatedAnimatedRectImpl(const glm::vec2& position, const glm::vec2& size, float zDepth, const glm::vec3& tint, float angle, Ref<Animation> animation);
	};

}