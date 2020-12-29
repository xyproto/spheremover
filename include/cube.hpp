#pragma once

#include <cmath>
#include <iomanip>
#include <limits>
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
const Vec3 Cube::normal(const Vec3 p) const
{

    // BAH. None of the plans work. This function is a work in progress.

    // 1. Find the closest three points on the cube.
    // 2. Treat those three points as a face and find the normal from that.
    // 3. ::intify that normal to get a cube normal.

    Points xs = this->points();

    // TODO: This can be made faster by passing in a distance_squared cache pointer to
    //       each *_closest_* function call.
    size_t smallest_ai = index_closest(xs, p);
    size_t smallest_bi = index_closest_except(xs, p, std::vector<size_t> { smallest_ai });
    size_t smallest_ci
        = index_closest_except(xs, p, std::vector<size_t> { smallest_ai, smallest_bi });
    size_t smallest_di = index_closest_except(
        xs, p, std::vector<size_t> { smallest_ai, smallest_bi, smallest_ci });

    // Okay, now create vectors that are from the center of the cube to these 3 closest points
    const Vec3 av = xs[smallest_ai] - m_pos;
    const Vec3 bv = xs[smallest_bi] - m_pos;
    const Vec3 cv = xs[smallest_ci] - m_pos;
    const Vec3 dv = xs[smallest_di] - m_pos;

    // Average the vectors

    const Vec3 average_closest = (av + bv + cv + dv) / 4;

    // Just return the clostest vertex, from the center and to that one,
    // then normalize and intify.
    // return av.normalize().intify();

    // Normalize the average

    const Vec3 average_closest_normalized = average_closest.normalize();

    // Intify the averaged normal to get a normal that points straight out

    return average_closest_normalized.intify();
}
