#pragma once

namespace Engine {

	class Layer
	{
	public:
		Layer() {};
		virtual ~Layer() = default;

		virtual void OnUpdate(float dt) {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
	};

}

