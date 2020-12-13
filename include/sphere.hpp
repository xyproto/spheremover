#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "point.hpp"
#include "vec3.hpp"

using namespace std::string_literals;

// Sphere has a position and a radius
class Sphere {
protected:
    const Point3 m_pos;
    const double m_radius;

public:
    Sphere(double _x, double _y, double _z, double _r)
        : m_pos { _x, _y, _z }
        , m_radius { _r }
    {
    }
    Sphere(const Point3 _pos, double _r)
        : m_pos { _pos }
        , m_radius { _r }
    {
    }
    const std::string str() const;
    double x() const;
    double y() const;
    double z() const;
    double r() const;
    double radius() const;
    double radius_squared() const;
    const Point3 pos() const;
    const Vec3 normal(const Point3 p) const;
};

// str returns a string representation of the sphere
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Sphere::str() const
{
    std::stringstream ss;
    ss << "sphere: ("s << m_pos << ", "s << m_radius << ")"s;
    return ss.str();
}

// Implement support for the << operator, by calling the Vec3 str method
inline std::ostream& operator<<(std::ostream& os, const Sphere& s)
{
    os << s.str();
    return os;
}

double Sphere::x() const { return m_pos.x(); }

double Sphere::y() const { return m_pos.y(); }

double Sphere::z() const { return m_pos.z(); }

double Sphere::r() const { return m_radius; }

double Sphere::radius() const { return m_radius; }

double Sphere::radius_squared() const { return m_radius * m_radius; }

const Point3 Sphere::pos() const { return m_pos; }

// Get the normal sticking out from the sphere at the point p on the surface of the sphere
const Vec3 Sphere::normal(const Point3 p) const { return (p - m_pos) / m_radius; }
