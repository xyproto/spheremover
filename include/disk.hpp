#pragma once

// A 2D circle in 3D space

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "vec3.hpp"

using namespace std::string_literals;

// Disk has a position and a radius vector
class Disk {
protected:
    const Vec3 m_pos;
    const Vec3 m_radius_vector;

public:
    Disk(double _x, double _y, double _z, double _rx, double _ry, double _rz)
        : m_pos { _x, _y, _z }
        , m_radius_vector { _rx, _ry, _rz }
    {
    }

    Disk(double _x, double _y, double _z, double _r) // same radius for x and y, but flat z
        : m_pos { _x, _y, _z }
        , m_radius_vector { _r, _r, 0.0 }
    {
    }

    Disk(const Vec3 _pos, const Vec3 _rv)
        : m_pos { _pos }
        , m_radius_vector { _rv }
    {
    }

    Disk(const Vec3 _pos, const double _r) // same radius for x and y, but flat z
        : m_pos { _pos }
        , m_radius_vector { _r, _r, 0.0 }
    {
    }

    const std::string str() const;

    double x() const;
    double y() const;
    double z() const;
    double rx() const;
    double ry() const;
    double rz() const;

    const Vec3 radius() const;

    const Vec3 pos() const;
    const Vec3 normal(const Vec3 p) const;
};

// str returns a string representation of the circle
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Disk::str() const
{
    std::stringstream ss;
    ss << "circle: ("s << m_pos << ", "s << m_radius_vector << ")"s;
    return ss.str();
}

// Implement support for the << operator, by calling the Vec3 str method
inline std::ostream& operator<<(std::ostream& os, const Disk& s)
{
    os << s.str();
    return os;
}

double Disk::x() const { return m_pos.x(); }

double Disk::y() const { return m_pos.y(); }

double Disk::z() const { return m_pos.z(); }

double Disk::rx() const { return m_radius_vector.x(); }

double Disk::ry() const { return m_radius_vector.y(); }

double Disk::rz() const { return m_radius_vector.z(); }

const Vec3 Disk::radius() const { return m_radius_vector; }

const Vec3 Disk::pos() const { return m_pos; }

// Get the normal sticking out from the disk at the point p on the surface of the disk
/*const Vec3 Disk::normal(const Vec3 p) const
{
    // for a disk
    // return (p - m_pos) / m_radius;}
    throw "not implemented";
}
*/
