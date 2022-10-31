#pragma once
#include "SmoothOptions.h"
#include "ResizeOptions.h"

#include "json.hpp"

using nlohmann::json;

class ImageOptions {
public:
	SmoothOptions smoothOptions;
	ResizeOptions resizeOptions;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ImageOptions, smoothOptions, resizeOptions)
};