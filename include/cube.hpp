#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "points.hpp"
#include "vec3.hpp"

using namespace std::string_literals;

// Cube has a position, a width (x), a height (y) and a depth (z)
class Cube {
protected:
    const Vec3 m_pos; // center position of the cube
    const double m_whd[3]; // width, height and depth

public:
    Cube(double _x, double _y, double _z, double _w, double _h, double _d)
        : m_pos { _x, _y, _z }
        , m_whd { _w, _h, _d }
    {
    }

    Cube(double _x, double _y, double _z, double _whd) // same width, height and depth
        : m_pos { _x, _y, _z }
        , m_whd { _whd, _whd, _whd }
    {
    }

    Cube(const Vec3 _pos, double _w, double _h, double _d)
        : m_pos { _pos }
        , m_whd { _w, _h, _d }
    {
    }

    Cube(const Vec3 _pos, double _whd) // same width, height and depth
        : m_pos { _pos }
        , m_whd { _whd, _whd, _whd }
    {
    }

    const std::string str() const;
    double x() const;
    double y() const;
    double z() const;
    double w() const;
    double h() const;
    double d() const;
    const Vec3 pos() const;
    const Vec3 normal(const Vec3 p) const;

    const Vec3 p0() const;
    const Vec3 p1() const;
    const Vec3 p2() const;
    const Vec3 p3() const;
    const Vec3 p4() const;
    const Vec3 p5() const;
    const Vec3 p6() const;
    const Vec3 p7() const;

    const Points points() const;
};

// str returns a string representation of the cube
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Cube::str() const
{
    std::stringstream ss;
    ss << "cube: ("s << m_pos << ", "s << m_whd[0] << ", "s << m_whd[1] << ", "s << m_whd[2]
       << ")"s;
    return ss.str();
}

// Implement support for the << operator, by calling the Vec3 str method
inline std::ostream& operator<<(std::ostream& os, const Cube& s)
{
    os << s.str();
    return os;
}

double Cube::x() const { return m_pos.x(); }

double Cube::y() const { return m_pos.y(); }

double Cube::z() const { return m_pos.z(); }

double Cube::w() const { return m_whd[0]; }

double Cube::h() const { return m_whd[1]; }

double Cube::d() const { return m_whd[2]; }

const Vec3 Cube::pos() const { return m_pos; }

// m_pos is the center position
// rv is the "radius offset

// left bottom front point of the cube (-, -, -)
const Vec3 Cube::p0() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    // const double r = m_w / 2.0;

    return m_pos + Vec3 { -r0, -r1, -r2 };
}

// right bottom front point of the cube (+, -, -)
const Vec3 Cube::p1() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    // const double r = m_w / 2.0;

    return m_pos + Vec3 { r0, -r1, -r2 };
}

// right bottom back point of the cube (+, -, +)
const Vec3 Cube::p2() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    // const double r = m_w / 2.0;

    return m_pos + Vec3 { r0, -r1, r2 };
}

// left bottom back point of the cube (-, -, +)
const Vec3 Cube::p3() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    // const double r = m_w / 2.0;

    return m_pos + Vec3 { -r0, -r1, r2 };
}

// left top front point of the cube (-, +, -)
const Vec3 Cube::p4() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    // const double r = m_w / 2.0;

    return m_pos + Vec3 { -r0, r1, -r2 };
}

// right top front point of the cube (+, +, -)
const Vec3 Cube::p5() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    // const double r = m_w / 2.0;

    return m_pos + Vec3 { r0, r1, -r2 };
}

// right top back point of the cube (+, +, +)
const Vec3 Cube::p6() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    return m_pos + Vec3 { r0, r1, r2 };
}

// left top back point of the cube (-, +, +)
const Vec3 Cube::p7() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    return m_pos + Vec3 { -r0, r1, r2 };
}

// points returns a vector of ordered points for this cube
const Points Cube::points() const
{
    const double r0 = m_whd[0] / 2.0;
    const double r1 = m_whd[1] / 2.0;
    const double r2 = m_whd[2] / 2.0;

    return Points {
        std::move(m_pos + Vec3 { -r0, -r1, -r2 }),
        std::move(m_pos + Vec3 { r0, -r1, -r2 }),
        std::move(m_pos + Vec3 { r0, -r1, r2 }),
        std::move(m_pos + Vec3 { -r0, -r1, r2 }),
        std::move(m_pos + Vec3 { -r0, r1, -r2 }),
        std::move(m_pos + Vec3 { r0, r1, -r2 }),
        std::move(m_pos + Vec3 { r0, r1, r2 }),
        std::move(m_pos + Vec3 { -r0, r1, r2 }),
    };
}

// Get the normal sticking out from the cube at the point p on the surface of the cube
/*const Vec3 Cube::normal(const Vec3 p) const
{
    throw "not implemented!";
    // for a circle:
    // return (p - m_pos) / m_radius;
}
*/
