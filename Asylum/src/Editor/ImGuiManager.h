#pragma once

namespace Asylum {

	class ImGuiManager
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin();
		static void End();
	};

}