#pragma once
#include <string>
class ImageHandler
{
private:
	std::string imagePath;
public:
	void Open(std::string filepath);
	void Smooth(int kernelSize = 150, int kernelWidth = 70);
	void Scale(float factor);
	void Normalize();
};

