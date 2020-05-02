#pragma once

#include <memory>
#include <functional>

namespace Asylum {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#define AM_BIND_FN_1(fn) std::bind(&fn, this, std::placeholders::_1)
#define AM_BIND_FN_2(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2)