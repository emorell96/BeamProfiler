#pragma once
#include "json.hpp"

class ResizeOptions
{
public:
	bool GetResize() {
		return resize;
	}

	double GetResizeFactor() {
		return resizeFactor;
	}
	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResizeOptions, resize, resizeFactor)


private:
	bool resize = true;
	double resizeFactor = 0.25;
};