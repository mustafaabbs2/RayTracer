#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Define a 3D vector class
class Vec3 {
public:
    double x, y, z;

    Vec3() {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(double s) const {
        return Vec3(x * s, y * s, z * s);
    }

    Vec3 operator/(double s) const {
        return Vec3(x / s, y / s, z / s);
    }

    double dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3 cross(const Vec3& v) const {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        double len = length();
        return Vec3(x / len, y / len, z / len);
    }
};

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


// Utility function to clamp a value between a minimum and maximum
double clamp(double value, double min, double max) {
    return std::fmax(min, std::fmin(value, max));
}

// Utility function to compute the dot product of two vectors
double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Utility function to compute the cross product of two vectors
Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

Vec3 normalize(const Vec3& a)
{
    float length = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return Vec3(a.x / length, a.y / length, a.z / length);
}


// Utility function to compute the reflect direction of a vector given a surface normal
Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

// Compute the intersection of a ray with a sphere
bool intersectSphere(const Ray& ray, const Vec3& center, double radius, double& t) {
    Vec3 oc = ray.origin - center;
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(oc, ray.direction);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }
    else {
        double t0 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
        if (t0 > 0) {
            t = t0;
            return true;
        }
        else if (t1 > 0) {
            t = t1;
            return true;
        }
        else {
            return false;
        }
    }
}

// Define a ray class
class Ray {
public:
    Vec3 origin, direction;

    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

    Vec3 pointAt(double t) const {
        return origin + direction * t;
    }
};


int main() {
    // Image dimensions
    const int width = 640;
    const int height = 480;

    // Camera position and orientation
    Vec3 cameraPosition(0, 0, 0);
    Vec3 cameraDirection(0, 0, -1);
    Vec3 cameraUp(0, 1, 0);
    double fov = 60;

    // Scene objects
    Vec3 sphereCenter(0, 0, -5);
    double sphereRadius = 2;
    Color sphereColor(1, 0, 0);

    // Render the scene
    std::vector<Color> pixels(width * height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double x = (2.0 * i - width) / height;
            double y = (2.0 * j - height) / height;
            Vec3 rayDirection = normalize(cameraDirection + x * tan(fov / 2) * cross(cameraUp, cameraDirection) + y * tan(fov / 2) * cameraUp);
            Ray ray(cameraPosition, rayDirection);
            double t;
            if (intersectSphere(ray, sphereCenter, sphereRadius, t)) {
                pixels[j * width + i] = sphereColor;
            }
            else {
                pixels[j * width + i] = Color(0, 0, 0);
            }
        }
    }

    // Output the image in PPM format
    std::ofstream outfile("output.ppm");
    outfile << "P3\n" << width << " " << height << "\n255\n";
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = pixels[j * width + i];
            int r = (int)(255 * clamp(pixel.r, 0, 1));
            int g = (int)(255 * clamp(pixel.g, 0, 1));
            int b = (int)(255 * clamp(pixel.b, 0, 1));
            outfile << r << " " << g << " " << b << " ";
        }
        outfile << "\n";
    }

    return 0;
}
