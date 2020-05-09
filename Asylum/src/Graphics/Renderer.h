#pragma once

#include <array>

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
		
		// API
		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angle = 0.0f);
		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& tint = { 255,255,255,255 }, float angle = 0.0f);
		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const Ref<Animation>& animation, const glm::vec4& tint = { 255,255,255,255 }, float angle = 0.0f);
	private:
		static void Flush();
		
		static void FullBufferCheck();
		static float TextureChecks(uint32_t textureID);
		static void AssignVerticesToBuffer(float textureIndex, const glm::vec2& position, const glm::vec2& size, const glm::vec4& tint, const std::array<glm::vec2, 4>& textureCoords, float angle);
	};

}