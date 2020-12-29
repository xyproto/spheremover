#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std::string_literals;

// Vec3 is a fast 3D Vector class, using doubles in an array.
// In addition to this, the values are constant.
// Calculations will need to return new vectors.
class Vec3 {
protected:
    const double v[3];

public:
    Vec3(const double _x, const double _y, const double _z)
        : v { _x, _y, _z }
    {
    }

    const Vec3 operator+(const Vec3& a) const; // addition
    const Vec3 operator-(const Vec3& a) const; // subtraction
    const Vec3 operator*(const double d) const; // scale
    const Vec3 operator/(const double d) const; // div
    double dot(const Vec3& a) const; // dot product
    const Vec3 cross(const Vec3& a) const; // cross product
    double len() const; // length from (0,0,0)
    double len_squared() const; // length from (0,0,0), squared
    bool operator<(const Vec3& a) const; // less than, without using sqrt
    bool operator>(const Vec3& a) const; // greater than, without using sqrt
    const Vec3 normalize() const; // the normalized version
    const std::string str() const;

    double x() const;
    double y() const;
    double z() const;

    const Vec3 clamp255() const;
    const std::string ppm() const;

    double R() const;
    double G() const;
    double B() const;

    double distance(const Vec3& a) const; // length to another Vec3
    double distance_squared(const Vec3& a) const; // length to another Vec3, squared

    const Vec3 intify() const; // the integer part of each element

    // The assign operator can not be implemented, since Vec3 is always const
    // Vec3& operator=(Vec3&&); // needed by std::sort
};

// Add components
inline const Vec3 Vec3::operator+(const Vec3& a) const
{
    return Vec3 { v[0] + a.v[0], v[1] + a.v[1], v[2] + a.v[2] };
}

// Subtract components
inline const Vec3 Vec3::operator-(const Vec3& a) const
{
    return Vec3 { v[0] - a.v[0], v[1] - a.v[1], v[2] - a.v[2] };
}

// Scale by a double
inline const Vec3 Vec3::operator*(const double d) const
{
    return Vec3 { v[0] * d, v[1] * d, v[2] * d };
}

// Div by a double
inline const Vec3 Vec3::operator/(const double d) const
{
    const double r = (1.0 / d);
    return Vec3 { v[0] * r, v[1] * r, v[2] * r };
}

// Dot product
inline double Vec3::dot(const Vec3& a) const
{
    return v[0] * a.v[0] + v[1] * a.v[1] + v[2] * a.v[2];
}

// Cross product
inline const Vec3 Vec3::cross(const Vec3& a) const
{
    return Vec3 { v[1] * a.v[2] - v[2] * a.v[1], v[2] * a.v[0] - v[0] * a.v[2],
        v[0] * a.v[1] - v[1] * a.v[0] };
}

// Length; distance from (0, 0, 0)
inline double Vec3::len() const { return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }

// Length; distance from (0, 0, 0), squared
inline double Vec3::len_squared() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }

// Less than, without using sqrt
inline bool Vec3::operator<(const Vec3& a) const
{
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
        < (a.v[0] * a.v[0] + a.v[1] * a.v[1] + a.v[2] * a.v[2]);
}

// Greater than, without using sqrt
inline bool Vec3::operator>(const Vec3& a) const
{
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
        > (a.v[0] * a.v[0] + a.v[1] * a.v[1] + a.v[2] * a.v[2]);
}

// Normalized version of the vector
inline const Vec3 Vec3::normalize() const
{
    const double l = this->len();
    return Vec3 { v[0] / l, v[1] / l, v[2] / l };
}

// str returns a string representation of the vector
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Vec3::str() const
{
    std::stringstream ss;
    ss << "["s << std::setprecision(3) << v[0] << ", "s << v[1] << ", "s << v[2] << "]"s;
    return ss.str();
}

inline double Vec3::x() const { return v[0]; }
inline double Vec3::y() const { return v[1]; }
inline double Vec3::z() const { return v[2]; }

// Implement support for the << operator, by calling the Vec3 str method
inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    os << v.str();
    return os;
}

inline bool operator==(const Vec3& a, const Vec3& b)
{
    return a.x() == b.x() && a.y() == b.y() && a.z() == b.z();
}

// Treat the Vec3 as an RGB color and clamp the values from 0 to 255
inline const Vec3 Vec3::clamp255() const
{
    // inspired by
    // https://github.com/MarcusMathiassen/BasicRaytracer30min/blob/master/basic_raytracer.cpp
    return Vec3 { (v[0] > 255) ? 255
            : (v[0] < 0)       ? 0
                               : v[0],
        (v[1] > 255)     ? 255
            : (v[1] < 0) ? 0
                         : v[1],
        (v[2] > 255)     ? 255
            : (v[2] < 0) ? 0
                         : v[2] };
}

// Output R, G and B, as space separated ints
inline const std::string Vec3::ppm() const
{
    return std::to_string(static_cast<int>(v[0])) + " "s + std::to_string(static_cast<int>(v[1]))
        + " "s + std::to_string(static_cast<int>(v[2]));
}

inline double Vec3::R() const { return v[0]; }

inline double Vec3::G() const { return v[1]; }

inline double Vec3::B() const { return v[2]; }

inline const Vec3 operator*(double d, const Vec3 v) { return v * d; }

inline const Vec3 operator/(double d, const Vec3 v) { return v * (1 / d); }

double Vec3::distance(const Vec3& a) const // distance to another Vec3
{
    return std::sqrt((v[0] - a.v[0]) * (v[0] - a.v[0]) + (v[1] - a.v[1]) * (v[1] - a.v[1])
        + (v[2] - a.v[2]) * (v[2] - a.v[2]));
}

double Vec3::distance_squared(const Vec3& a) const // distance to another Vec3, squared
{
    return (v[0] - a.v[0]) * (v[0] - a.v[0]) + (v[1] - a.v[1]) * (v[1] - a.v[1])
        + (v[2] - a.v[2]) * (v[2] - a.v[2]);
}

// Return a vec3 with only the integer parts of the coordinates.
// This can be used for finding the normal vectors of a cube,
// if the center of the cube is at (0,0,0).
inline const Vec3 Vec3::intify() const
{
    return Vec3 { static_cast<double>(static_cast<int>(v[0])),
        static_cast<double>(static_cast<int>(v[1])), static_cast<double>(static_cast<int>(v[2])) };
}
