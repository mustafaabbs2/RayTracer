#pragma once

#include <iostream>

// Define a color class with red, green, and blue components
class Color {
public:
    double r, g, b;

    Color() {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}

    Color operator*(double scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b);
    }

};

Color operator*(double x, const Color& other) {
    return Color(x * other.r, x * other.g, x * other.b);
}

Color operator*(const Color& other, double x) {
    return Color(x * other.r, x * other.g, x * other.b);
}



