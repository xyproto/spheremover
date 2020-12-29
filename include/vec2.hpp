#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std::string_literals;

// Vec2 is a fast 2D Vector class, using doubles in an array.
// In addition to this, the values are constant.
// Calculations will need to return new vectors.
class Vec2 {
protected:
    const double v[2];

public:
    Vec2(double _x, double _y)
        : v { _x, _y }
    {
    }

    const Vec2 operator+(const Vec2& a) const; // addition
    const Vec2 operator-(const Vec2& a) const; // subtraction
    const Vec2 operator*(const double d) const; // scale
    const Vec2 operator/(const double d) const; // div
    double dot(const Vec2& a) const; // dot product
    double len() const; // length from (0,0)
    double len_squared() const; // length from (0,0), squared
    bool operator<(const Vec2& a) const; // less than, without using sqrt
    bool operator>(const Vec2& a) const; // greater than, without using sqrt
    const Vec2 normalize() const; // the normalized version
    const std::string str() const;

    double x() const;
    double y() const;

    double R() const;
    double G() const;

    const Vec2 intify() const;
};

// Add components
inline const Vec2 Vec2::operator+(const Vec2& a) const
{
    return Vec2 { v[0] + a.v[0], v[1] + a.v[1] };
}

// Subtract components
inline const Vec2 Vec2::operator-(const Vec2& a) const
{
    return Vec2 { v[0] - a.v[0], v[1] - a.v[1] };
}

// Scale by a double
inline const Vec2 Vec2::operator*(const double d) const { return Vec2 { v[0] * d, v[1] * d }; }

// Div by a double
inline const Vec2 Vec2::operator/(const double d) const
{
    const double r = 1.0 / d;
    return Vec2 { v[0] * r, v[1] * r };
}

// Dot product
inline double Vec2::dot(const Vec2& a) const { return v[0] * a.v[0] + v[1] * a.v[1]; }

// Length; distance from (0, 0)
inline double Vec2::len() const { return std::sqrt(v[0] * v[0] + v[1] * v[1]); }

// Length; distance from (0, 0), squared
inline double Vec2::len_squared() const { return v[0] * v[0] + v[1] * v[1]; }

// Less than, without using sqrt
inline bool Vec2::operator<(const Vec2& a) const
{
    return (v[0] * v[0] + v[1] * v[1]) < (a.v[0] * a.v[0] + a.v[1] * a.v[1]);
}

// Greater than, without using sqrt
inline bool Vec2::operator>(const Vec2& a) const
{
    return (v[0] * v[0] + v[1] * v[1]) > (a.v[0] * a.v[0] + a.v[1] * a.v[1]);
}

// Normalized version of the vector
inline const Vec2 Vec2::normalize() const
{
    const double l = this->len();
    return Vec2 { v[0] / l, v[1] / l };
}

// str returns a string representation of the vector
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Vec2::str() const
{
    std::stringstream ss;
    ss << "["s << std::setprecision(3) << v[0] << ", "s << v[1] << "]"s;
    return ss.str();
}

// Implement support for the << operator, by calling the Vec2 str method
inline std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
    os << v.str();
    return os;
}

// Return the x component
inline double Vec2::x() const { return v[0]; }
// Return the y component
inline double Vec2::y() const { return v[1]; }

inline bool operator==(const Vec2& a, const Vec2& b) { return a.x() == b.x() && a.y() == b.y(); }

inline double Vec2::R() const { return v[0]; }

inline double Vec2::G() const { return v[1]; }
//
// Return a vec2 with only the integer parts of the coordinates.
// This can be used for finding the normal vectors of a square,
// if the center of the square is at (0,0).
inline const Vec2 Vec2::intify() const
{
    return Vec2 { static_cast<double>(static_cast<int>(v[0])),
        static_cast<double>(static_cast<int>(v[1])) };
}
