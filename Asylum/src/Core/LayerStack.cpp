#include "ampch.h"
#include "LayerStack.h"

namespace Asylum {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : mLayers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
		layer->OnAttach();
		layer->AddEventCallbacks();
		mLayerInsertIndex++;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, layer);
		if (it != mLayers.begin())
		{
			layer->OnDetach();
			mLayers.erase(it);
			mLayerInsertIndex--;
		}
	}

}

