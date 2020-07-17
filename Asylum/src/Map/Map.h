#pragma once

#include <vector>
#include "Core/Core.h"

#include "Map/MapLayer.h"

namespace Asylum {

	class Map
	{
	private:
		std::vector<Ref<MapLayer>> mMapLayers;
	public:
		Map();
		~Map();
	};

}