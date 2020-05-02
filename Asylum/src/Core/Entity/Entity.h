#pragma once

#include <glm/glm.hpp>
#include "Graphics/Renderer.h"

namespace Asylum {

	class CollisionMask {};

	class RectangleCollisionMask : public CollisionMask
	{
	public:
		glm::vec2 Position;
		glm::vec2 Size;

		RectangleCollisionMask(float x, float y, float w, float h)
			: Position({x, y}), Size({w, h})
		{}
	};

	class Entity
	{
	protected:
		glm::vec2 mPosition;
		glm::vec2 mSize;
		
		float mZDepth;

		CollisionMask mCollisionMask;
		bool mIsActive;
	public:
		Entity(const glm::vec2& position, const glm::vec2& size, float zDepth)
			: mPosition(position), mSize(size), mZDepth(zDepth), mIsActive(true)
		{}

		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;

		// getter
		inline const glm::vec2& GetPosition() const { return mPosition; };
		inline const glm::vec2& GetSize() const { return mSize; };
		inline float GetZDepth() const { return mZDepth; };
		inline const CollisionMask& GetCollisionMask() const { return mCollisionMask; };
		inline bool IsActive() const { return mIsActive; };
	};

}