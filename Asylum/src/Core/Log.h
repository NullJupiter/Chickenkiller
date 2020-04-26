#pragma once

#include <iostream>

#ifdef AM_DEBUG
	#define LOG(x) std::cout << x << std::endl;
#else 
	#define LOG(x)
#endif