#pragma once

#include "Utils.hpp"
#include "WriterInterface.hpp"
#include <fstream>
#include <memory>

class PPMWriter : public WriterInterface

{
public:
	PPMWriter(std::string filename, const int width, const int height);

	void WritePixelsToBuffer(const Color& pixel, const int samplesPerPixel) const override;

private:
	int _width, _height;
	std::string _filename;
	std::unique_ptr<std::ofstream> _outfile;
};