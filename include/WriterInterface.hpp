#pragma once

#include <vector>
#include "Color.hpp"


class WriterInterface{
public:
	WriterInterface() {}
	virtual void WritePixelToFile(const Color& pixel, const int samplesPerPixel) const = 0;

};