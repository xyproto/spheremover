#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std::string_literals;

// Vec4 is a fast 3D Vector class, using doubles in an array.
// In addition to this, the values are constant.
// Calculations will need to return new vectors.
class Vec4 {
protected:
    const double v[4];

public:
    Vec4(double _x, double _y, double _z, double _t)
        : v { _x, _y, _z, _t }
    {
    }

    const Vec4 operator+(const Vec4& a) const; // addition
    const Vec4 operator-(const Vec4& a) const; // subtraction
    const Vec4 operator*(const double d) const; // scale
    const Vec4 operator/(const double d) const; // div
    double dot(const Vec4& a) const; // dot product
    const Vec4 cross(const Vec4& a) const; // cross product
    double len() const; // length from (0,0,0,0)
    double len_squared() const; // length from (0,0,0,0), squared
    bool operator<(const Vec4& a) const; // less than, without using sqrt
    bool operator>(const Vec4& a) const; // greater than, without using sqrt
    const Vec4 normalize() const; // the normalized version
    const std::string str() const;

    double x() const;
    double y() const;
    double z() const;
    double t() const;

    double R() const;
    double G() const;
    double B() const;
    double A() const;

    const Vec4 intify() const;
};

// Add components
inline const Vec4 Vec4::operator+(const Vec4& a) const
{
    return Vec4 { v[0] + a.v[0], v[1] + a.v[1], v[2] + a.v[2], v[3] + a.v[3] };
}

// Subtract components
inline const Vec4 Vec4::operator-(const Vec4& a) const
{
    return Vec4 { v[0] - a.v[0], v[1] - a.v[1], v[2] - a.v[2], v[3] - a.v[3] };
}

// Scale by a double
inline const Vec4 Vec4::operator*(const double d) const
{
    return Vec4 { v[0] * d, v[1] * d, v[2] * d, v[3] * d };
}

// Div by a double
inline const Vec4 Vec4::operator/(const double d) const
{
    const double r = (1.0 / d);
    return Vec4 { v[0] * r, v[1] * r, v[2] * r, v[3] * r };
}

// Dot product
inline double Vec4::dot(const Vec4& a) const
{
    return v[0] * a.v[0] + v[1] * a.v[1] + v[2] * a.v[2] + v[3] * a.v[3];
}

// Length; distance from (0, 0, 0)
inline double Vec4::len() const { return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }

// Length; distance from (0, 0, 0), squared
inline double Vec4::len_squared() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }

// Less than, without using sqrt
inline bool Vec4::operator<(const Vec4& a) const
{
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
        < (a.v[0] * a.v[0] + a.v[1] * a.v[1] + a.v[2] * a.v[2]);
}

// Greater than, without using sqrt
inline bool Vec4::operator>(const Vec4& a) const
{
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3])
        > (a.v[0] * a.v[0] + a.v[1] * a.v[1] + a.v[2] * a.v[2] + a.v[3] * a.v[3]);
}

// Normalized version of the vector
inline const Vec4 Vec4::normalize() const
{
    const double l = this->len();
    return Vec4 { v[0] / l, v[1] / l, v[2] / l, v[3] / l };
}

// str returns a string representation of the vector
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Vec4::str() const
{
    std::stringstream ss;
    ss << "["s << std::setprecision(3) << v[0] << ", "s << v[1] << ", "s << v[2] << ", "s << v[3]
       << "]"s;
    return ss.str();
}

// Implement support for the << operator, by calling the Vec4 str method
inline std::ostream& operator<<(std::ostream& os, const Vec4& v)
{
    os << v.str();
    return os;
}

inline double Vec4::x() const { return v[0]; }

inline double Vec4::y() const { return v[1]; }

inline double Vec4::z() const { return v[2]; }

inline double Vec4::t() const { return v[3]; }

inline bool operator==(const Vec4& a, const Vec4& b)
{
    return a.x() == b.x() && a.y() == b.y() && a.z() == b.z() && a.t() == b.t();
}

inline double Vec4::R() const { return v[0]; }

inline double Vec4::G() const { return v[1]; }

inline double Vec4::B() const { return v[2]; }

inline double Vec4::A() const { return v[3]; }

// Return a vec4 with only the integer parts of the coordinates.
// This can be used for finding the normal vectors of a 4D cube,
// if the center of the cube is at (0,0,0,0).
inline const Vec4 Vec4::intify() const
{
    return Vec4 { static_cast<double>(static_cast<int>(v[0])),
        static_cast<double>(static_cast<int>(v[1])), static_cast<double>(static_cast<int>(v[2])),
        static_cast<double>(static_cast<int>(v[3])) };
}
