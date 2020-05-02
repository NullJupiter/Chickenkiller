#include "ampch.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Asylum {

	// renderer consts used to define how many rects can be drawn in one batch
	static const size_t sMaxRects = 4000;
	static const size_t sMaxVertices = sMaxRects * 4;
	static const size_t sMaxIndices = sMaxRects * 6;
	static const size_t sMaxTextureSlots = 8;

	struct RendererProperties
	{
		// vertex array and buffer objects
		uint32_t VAO = 0;
		uint32_t VBO = 0;
		uint32_t EBO = 0;

		// white texture for colored rects
		uint32_t WhiteTexture = 0;

		// CPU buffer for vertex data and a pointer to navigate in
		VertexData* RectBuffer = nullptr;
		VertexData* RectBufferPtr = nullptr;

		// how many indices have been used
		uint32_t IndicesCount = 0;

		// used to store the different texture ids
		// like a map (textureSlot -> textureID)
		uint32_t TextureSlots[sMaxTextureSlots];
		uint32_t TextureSlotIndex = 1;

		glm::vec4 RectStandardVertices[4];
	};

	static RendererProperties sRendererData;

	void Renderer::Init()
	{
		// initialize rect buffer
		sRendererData.RectBuffer = new VertexData[sMaxVertices];

		// gen VAO
		glGenVertexArrays(1, &sRendererData.VAO);
		glBindVertexArray(sRendererData.VAO);

		// gen VBO
		glGenBuffers(1, &sRendererData.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, sRendererData.VBO);
		glBufferData(GL_ARRAY_BUFFER, sMaxVertices * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

		// create indices
		uint32_t* indices = new uint32_t[sMaxIndices];

		int offset = 0;
		for (int i = 0; i < sMaxIndices; i+=6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		// gen EBO
		glGenBuffers(1, &sRendererData.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sRendererData.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * sMaxIndices, indices, GL_STATIC_DRAW);
		delete[] indices;

		// set position shader attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, Position));

		// set color shader attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, Color));

		// set tex coord shader attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, TexCoord));

		// set tex id shader attribute
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, TexSlot));

		// create 1x1 white texture
		glGenTextures(1, &sRendererData.WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, sRendererData.WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		uint32_t color = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

		// initialize texture slots array
		sRendererData.TextureSlots[0] = sRendererData.WhiteTexture;
		for (int i = 1; i < sMaxTextureSlots; i++)
			sRendererData.TextureSlots[i] = 0;

		// initialize standard rectangle vertices
		sRendererData.RectStandardVertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		sRendererData.RectStandardVertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		sRendererData.RectStandardVertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		sRendererData.RectStandardVertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer::Shutdown()
	{
		// delete vertex array and buffer objects
		glDeleteVertexArrays(1, &sRendererData.VAO);
		glDeleteBuffers(1, &sRendererData.VBO);
		glDeleteBuffers(1, &sRendererData.EBO);

		// delete the 1x1 white texturee
		glDeleteTextures(1, &sRendererData.WhiteTexture);
		
		// delete the CPU vertex buffer
		delete[] sRendererData.RectBuffer;
	}

	void Renderer::BeginDraw()
	{
		// set buffer pointer to beginning
		sRendererData.RectBufferPtr = sRendererData.RectBuffer;
	}

	void Renderer::EndDraw()
	{
		// upload vertex data to the GPU
		GLsizeiptr size = (uint8_t*)sRendererData.RectBufferPtr - (uint8_t*)sRendererData.RectBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, sRendererData.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, sRendererData.RectBuffer);

		Flush();
	}

	void Renderer::Flush()
	{
		// loop through all texture slots and bind the texture IDs to the corresponding texture slot
		for (uint32_t i = 0; i < sRendererData.TextureSlotIndex; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, sRendererData.TextureSlots[i]);
		}

		// bind the VAO and emit a draw call
		glBindVertexArray(sRendererData.VAO);
		glDrawElements(GL_TRIANGLES, sRendererData.IndicesCount, GL_UNSIGNED_INT, nullptr);

		// reset variables
		sRendererData.TextureSlotIndex = 1;
		sRendererData.IndicesCount = 0;
	}

	// DRAW IMPLEMENTATIONS

	void Renderer::DrawColoredRectImpl(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float zDepth)
	{
		// check if the maximum count of indices is being used
		// if this happens we end the batch, trigger a draw call and begin a new batch
		if (sRendererData.IndicesCount >= sMaxIndices)
		{
			EndDraw();
			BeginDraw();
		}

		// texture index is set to zero because for colored rects the white texture is being used
		float textureIndex = 0.0f;

		// convert rgba colors from 0-255 to 0-1
		const glm::vec4 rectColor = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };

		// insert vertex data into the CPU vertex buffer
		sRendererData.RectBufferPtr->Position = { position.x, position.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x + size.x, position.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x + size.x, position.y + size.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x, position.y + size.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		// increase the indices count for the amount of indices we needed for this rectangle
		sRendererData.IndicesCount += 6;
	}

	void Renderer::DrawRotatedColoredRectImpl(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float zDepth, float angle)
	{
		// check if the maximum count of indices is being used
		// if this happens we end the batch, trigger a draw call and begin a new batch
		if (sRendererData.IndicesCount >= sMaxIndices)
		{
			EndDraw();
			BeginDraw();
		}

		// texture index is set to zero because for colored rects the white texture is being used
		float textureIndex = 0.0f;

		// convert rgba colors from 0-255 to 0-1
		const glm::vec4 rectColor = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };

		// create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), {position.x, position.y, zDepth});
		transform = glm::rotate(transform, angle, { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, { size.x, size.y, 0.0f });

		// insert vertex data into the CPU vertex buffer
		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[0]);
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[1]);
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[2]);
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[3]);
		sRendererData.RectBufferPtr->Color = rectColor;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		// increase the indices count for the amount of indices we needed for this rectangle
		sRendererData.IndicesCount += 6;
	}

	void Renderer::DrawTexturedRectImpl(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth, const glm::vec3& tint)
	{
		// check if the maximum amount of indices is being used or all texture slots are being used
		// if this happens we end the batch, trigger a draw call and begin a new batch
		if (sRendererData.IndicesCount >= sMaxIndices || sRendererData.TextureSlotIndex >= sMaxTextureSlots)
		{
			EndDraw();
			BeginDraw();
		}

		// convert the tint color from rgb 0-255 to 0-1
		const glm::vec4 rectTint = { tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f, 1.0f };

		const uint32_t textureID = texture->GetID();

		// check if the texture we want to draw is already being used
		// if so use the same texture slot (so we don't waste texture slots)
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < sRendererData.TextureSlotIndex; i++)
		{
			if (sRendererData.TextureSlots[i] == textureID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		// if the texture is not in the texture slots array
		// assign it a new texture slot and increase the texture slot index
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)sRendererData.TextureSlotIndex;
			sRendererData.TextureSlots[sRendererData.TextureSlotIndex] = textureID;
			sRendererData.TextureSlotIndex++;
		}

		// insert vertex data into the CPU vertex buffer
		sRendererData.RectBufferPtr->Position = { position.x, position.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x + size.x, position.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x + size.x, position.y + size.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x, position.y + size.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		// increase the indices count for the amount of indices we needed for this rectangle
		sRendererData.IndicesCount += 6;
	}

	void Renderer::DrawRotatedTexturedRectImpl(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth, const glm::vec3& tint, float angle)
	{
		// check if the maximum amount of indices is being used or all texture slots are being used
		// if this happens we end the batch, trigger a draw call and begin a new batch
		if (sRendererData.IndicesCount >= sMaxIndices || sRendererData.TextureSlotIndex >= sMaxTextureSlots)
		{
			EndDraw();
			BeginDraw();
		}

		// convert the tint color from rgb 0-255 to 0-1
		const glm::vec4 rectTint = { tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f, 1.0f };

		const uint32_t textureID = texture->GetID();

		// check if the texture we want to draw is already being used
		// if so use the same texture slot (so we don't waste texture slots)
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < sRendererData.TextureSlotIndex; i++)
		{
			if (sRendererData.TextureSlots[i] == textureID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		// if the texture is not in the texture slots array
		// assign it a new texture slot and increase the texture slot index
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)sRendererData.TextureSlotIndex;
			sRendererData.TextureSlots[sRendererData.TextureSlotIndex] = textureID;
			sRendererData.TextureSlotIndex++;
		}

		// create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, zDepth });
		transform = glm::rotate(transform, angle, { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, { size.x, size.y, 0.0f });

		// insert vertex data into the CPU vertex buffer
		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[0]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[1]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 0.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[2]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 1.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[3]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = { 0.0f, 1.0f };
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		// increase the indices count for the amount of indices we needed for this rectangle
		sRendererData.IndicesCount += 6;
	}


	void Renderer::DrawAnimatedRectImpl(const glm::vec2& position, const glm::vec2& size, float zDepth, const glm::vec3& tint, Ref<Animation> animation)
	{
		// check if the maximum amount of indices is being used or all texture slots are being used
		// if this happens we end the batch, trigger a draw call and begin a new batch
		if (sRendererData.IndicesCount >= sMaxIndices || sRendererData.TextureSlotIndex >= sMaxTextureSlots)
		{
			EndDraw();
			BeginDraw();
		}

		// convert the tint color from rgb 0-255 to 0-1
		const glm::vec4 rectTint = { tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f, 1.0f };

		const uint32_t textureID = animation->GetTextureID();

		// check if the texture we want to draw is already being used
		// if so use the same texture slot (so we don't waste texture slots)
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < sRendererData.TextureSlotIndex; i++)
		{
			if (sRendererData.TextureSlots[i] == textureID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		// if the texture is not in the texture slots array
		// assign it a new texture slot and increase the texture slot index
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)sRendererData.TextureSlotIndex;
			sRendererData.TextureSlots[sRendererData.TextureSlotIndex] = textureID;
			sRendererData.TextureSlotIndex++;
		}

		const std::vector<glm::vec2>& texCoords = animation->GetCurrentTextureCoords();

		// insert vertex data into the CPU vertex buffer
		sRendererData.RectBufferPtr->Position = { position.x, position.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[0];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x + size.x, position.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[1];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x + size.x, position.y + size.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[2];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = { position.x, position.y + size.y, zDepth };
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[3];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		// increase the indices count for the amount of indices we needed for this rectangle
		sRendererData.IndicesCount += 6;
	}

	void Renderer::DrawRotatedAnimatedRectImpl(const glm::vec2& position, const glm::vec2& size, float zDepth, const glm::vec3& tint, float angle, Ref<Animation> animation)
	{
		// check if the maximum amount of indices is being used or all texture slots are being used
		// if this happens we end the batch, trigger a draw call and begin a new batch
		if (sRendererData.IndicesCount >= sMaxIndices || sRendererData.TextureSlotIndex >= sMaxTextureSlots)
		{
			EndDraw();
			BeginDraw();
		}

		// convert the tint color from rgb 0-255 to 0-1
		const glm::vec4 rectTint = { tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f, 1.0f };

		const uint32_t textureID = animation->GetTextureID();

		// check if the texture we want to draw is already being used
		// if so use the same texture slot (so we don't waste texture slots)
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < sRendererData.TextureSlotIndex; i++)
		{
			if (sRendererData.TextureSlots[i] == textureID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		// if the texture is not in the texture slots array
		// assign it a new texture slot and increase the texture slot index
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)sRendererData.TextureSlotIndex;
			sRendererData.TextureSlots[sRendererData.TextureSlotIndex] = textureID;
			sRendererData.TextureSlotIndex++;
		}

		// create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, zDepth });
		transform = glm::rotate(transform, angle, { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, { size.x, size.y, 0.0f });

		const std::vector<glm::vec2> texCoords = animation->GetCurrentTextureCoords();

		// insert vertex data into the CPU vertex buffer
		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[0]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[0];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[1]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[1];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[2]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[2];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		sRendererData.RectBufferPtr->Position = glm::vec3(transform * sRendererData.RectStandardVertices[3]);
		sRendererData.RectBufferPtr->Color = rectTint;
		sRendererData.RectBufferPtr->TexCoord = texCoords[3];
		sRendererData.RectBufferPtr->TexSlot = textureIndex;
		sRendererData.RectBufferPtr++;

		// increase the indices count for the amount of indices we needed for this rectangle
		sRendererData.IndicesCount += 6;
	}

	// API CALLS //

	// colored rect calls
	void Renderer::DrawColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawColoredRectImpl(position, size, color, 0.0f);
	}

	void Renderer::DrawColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float zDepth)
	{
		DrawColoredRectImpl(position, size, color, zDepth);
	}

	// rotated colored rect calls
	void Renderer::DrawRotatedColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angle)
	{
		DrawRotatedColoredRectImpl(position, size, color, 0.0f, angle);
	}

	void Renderer::DrawRotatedColoredRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angle, float zDepth)
	{
		DrawRotatedColoredRectImpl(position, size, color, zDepth, angle);
	}

	// texture rect calls
	void Renderer::DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture)
	{
		DrawTexturedRectImpl(position, size, texture, 0.0f, { 255, 255, 255 });
	}

	void Renderer::DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth)
	{
		DrawTexturedRectImpl(position, size, texture, zDepth, { 255, 255, 255 });
	}

	void Renderer::DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, const glm::vec3& tint)
	{
		DrawTexturedRectImpl(position, size, texture, 0.0f, tint);
	}

	void Renderer::DrawTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float zDepth, const glm::vec3& tint)
	{
		DrawTexturedRectImpl(position, size, texture, zDepth, tint);
	}

	// rotated textured rect calls
	void Renderer::DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle)
	{
		DrawRotatedTexturedRectImpl(position, size, texture, 0.0f, { 255,255,255 }, angle);
	}

	void Renderer::DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle, float zDepth)
	{
		DrawRotatedTexturedRectImpl(position, size, texture, zDepth, { 255,255,255 }, angle);
	}

	void Renderer::DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle, const glm::vec3& tint)
	{
		DrawRotatedTexturedRectImpl(position, size, texture, 0.0f, tint, angle);
	}

	void Renderer::DrawRotatedTexturedRect(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, float angle, float zDepth, const glm::vec3& tint)
	{
		DrawRotatedTexturedRectImpl(position, size, texture, zDepth, tint, angle);
	}

	// animated rect calls
	void Renderer::DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, Ref<Animation> animation)
	{
		DrawAnimatedRectImpl(position, size, 0.0f, { 255,255,255 }, animation);
	}

	void Renderer::DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, float zDepth, Ref<Animation> animation)
	{
		DrawAnimatedRectImpl(position, size, zDepth, { 255,255,255 }, animation);
	}

	void Renderer::DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& tint, Ref<Animation> animation)
	{
		DrawAnimatedRectImpl(position, size, 0.0f, tint, animation);
	}

	void Renderer::DrawAnimatedRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& tint, float zDepth, Ref<Animation> animation)
	{
		DrawAnimatedRectImpl(position, size, zDepth, tint, animation);
	}

	void Renderer::DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, Ref<Animation> animation)
	{
		DrawRotatedAnimatedRectImpl(position, size, 0.0f, { 255,255,255 }, angle, animation);
	}

	void Renderer::DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& tint, Ref<Animation> animation)
	{
		DrawRotatedAnimatedRectImpl(position, size, 0.0f, tint, angle, animation);
	}

	void Renderer::DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, float zDepth, Ref<Animation> animation)
	{
		DrawRotatedAnimatedRectImpl(position, size, zDepth, { 255,255,255 }, angle, animation);
	}

	void Renderer::DrawRotatedAnimatedRect(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& tint, float zDepth, Ref<Animation> animation)
	{
		DrawRotatedAnimatedRectImpl(position, size, zDepth, tint, angle, animation);
	}

	

}