#pragma once

#include "WriterInterface.hpp"
#include <iostream>
#include <fstream>
#include "Utils.hpp"



class PPMWriter : public WriterInterface 

{
public:
	PPMWriter(std::string filename, const int width, const int height) :_filename(filename), _width(width), _height(height) {
        _outfile = std::make_unique<std::ofstream>(filename);

        if (!filename.empty())
            *_outfile << "P3\n" << _width << " " << _height << "\n255\n";
        else
            throw std::exception("Empty file name \n");
    }

	void WritePixelToFile(const Color& pixel, const int samplesPerPixel) const override;

private:
    int _width, _height;
    std::string _filename;
    std::unique_ptr<std::ofstream> _outfile;

};

// Output the image in PPM format
void PPMWriter::WritePixelToFile(const Color& pixel, const int samplesPerPixel) const
{
    auto r = pixel.r;
    auto g = pixel.g;
    auto b = pixel.b;

    auto scale = 1.0 / samplesPerPixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);
    ////https://en.wikipedia.org/wiki/Gamma_correction

    auto r_p = static_cast<int>(255 * clamp(r, 0, 1));
    auto g_p = static_cast<int>(255 * clamp(g, 0, 1));
    auto b_p = static_cast<int>(255 * clamp(b, 0, 1));

    *_outfile << r_p << " " << g_p << " " << b_p << " " << "\n";
        
}
