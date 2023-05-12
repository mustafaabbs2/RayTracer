#pragma once

#include "Color.hpp"
#include <vector>

class WriterInterface
{
public:
	WriterInterface() { }
	virtual void WritePixelToFile(const Color& pixel, const int samplesPerPixel) const = 0;
};