#pragma once

#include <vector>
#include "Color.hpp"


class WriterInterface{
public:
	WriterInterface() {}
	virtual void WriteFile(const std::vector<Color>& pixels) const = 0;

};