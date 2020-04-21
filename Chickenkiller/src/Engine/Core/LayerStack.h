#pragma once

#include "Engine/Core/Layer.h"

#include <vector>

namespace Engine {

	class LayerStack
	{
	private:
		std::vector<Layer*> mLayers;
		uint32_t mLayerInsertIndex = 0;
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return mLayers.begin(); };
		std::vector<Layer*>::iterator end() { return mLayers.end(); };

	};

}

