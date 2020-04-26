#pragma once

namespace Asylum {

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

