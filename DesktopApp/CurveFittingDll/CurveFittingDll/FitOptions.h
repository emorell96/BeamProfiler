#pragma once
#include "FitParameters.h"
#include "ImageOptions.h"
#include "json.hpp"

class FitOptions
{
public:
	FitParameters fitParameters;
	ImageOptions imageOptions;
	std::string filePath;

	
private:

};

void from_json(const json& j, FitOptions& p) {
	j.at("filePath").get_to(p.filePath);
	p.fitParameters = j.at("fitParameters").get<FitParameters>();
	
};

void to_json(json& j, const FitOptions& p) {
	j = json{ {} };
}
