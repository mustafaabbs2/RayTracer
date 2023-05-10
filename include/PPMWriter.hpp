#pragma once

#include "WriterInterface.hpp"
#include <iostream>
#include <fstream>
#include "Utils.hpp"



class PPMWriter : public WriterInterface 

{
public:
	int _width, _height;
	PPMWriter(const int width, const int height) :_width(width), _height(height) {}

	void WriteFile(const std::vector<Color>& pixels) const override; 

};

// Output the image in PPM format
void PPMWriter::WriteFile(const std::vector<Color>& pixels) const 
{
    std::ofstream outfile("output.ppm");
    outfile << "P3\n" << _width << " " << _height << "\n255\n";
    for (int j = 0; j < _height; j++) {
        for (int i = 0; i < _width; i++) {
            Color pixel = pixels[j *_width + i];
            int r = (int)(255 * clamp(pixel.r, 0, 1));
            int g = (int)(255 * clamp(pixel.g, 0, 1));
            int b = (int)(255 * clamp(pixel.b, 0, 1));
            outfile << r << " " << g << " " << b << " ";
        }
        outfile << "\n";
    }

}
