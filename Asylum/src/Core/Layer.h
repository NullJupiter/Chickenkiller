#pragma once

namespace Asylum {

	class Layer
	{
	public:
		Layer() {};
		virtual ~Layer() = default;

		virtual void OnUpdate(float dt) = 0;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void AddEventCallbacks() {};
	};

}

