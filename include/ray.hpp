#pragma once

#include <cmath>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

#include "point.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

#include "plane.hpp"
#include "sphere.hpp"

using namespace std::string_literals;

class Ray {
protected:
    const Point3 m_p0; // start of ray
    const Point3 m_p1; // end of ray
    const Vec3 m_direction; // the direction the ray is pointing (this is m_p1 - m_p0, but it's
                            // useful to cache)

public:
    Ray(double _p0x, double _p0y, double _p0z, double _p1x, double _p1y, double _p1z)
        : m_p0 { _p0x, _p0y, _p0z }
        , m_p1 { _p1x, _p1y, _p1z }
        , m_direction { m_p1 - m_p0 }
    {
    }
    Ray(const Point3 _p0, const Point3 _p1)
        : m_p0 { _p0 }
        , m_p1 { _p1 }
        , m_direction { m_p1 - m_p0 }
    {
    }
    Ray(const Point3 viewPoint, const Point2 screenPosition)
        : m_p0 { viewPoint }
        , m_p1 { screenPosition.x(), screenPosition.y(), 0 }
        , m_direction { m_p1 - m_p0 }
    {
    }
    const std::optional<std::pair<const Point3, const Vec3>> intersect(const Sphere& sphere) const;
    const std::optional<std::pair<const Point3, const Vec3>> intersect(const Plane& plane) const;
    const std::optional<std::pair<const Point3, const Vec3>> intersect(const Cube& cube) const;

    const std::string str() const;

    // TODO: Save ray direction in class at init?
    const Vec3 direction() const;
};

// ray sphere intersection
// intersect returns the hit point and normal from the hit point and out from the center of the
// sphere if there is no intersection, nullopt is returned
inline const std::optional<std::pair<const Point3, const Vec3>> Ray::intersect(
    const Sphere& sphere) const
{
    // ray start
    const auto x0 = m_p0.x();
    const auto y0 = m_p0.y();
    const auto z0 = m_p0.z();

    const auto dx = direction().x();
    const auto dy = direction().y();
    const auto dz = direction().z();

    const auto cx = sphere.x(); // center x
    const auto cy = sphere.y(); // center y
    const auto cz = sphere.z(); // center z

    const auto a = dx * dx + dy * dy + dz * dz;
    const auto b = 2 * dx * (x0 - cx) + 2 * dy * (y0 - cy) + 2 * dz * (z0 - cz);
    const auto c = cx * cx + cy * cy + cz * cz + x0 * x0 + y0 * y0 + z0 * z0
        + (-2 * (cx * x0 + cy * y0 + cz * z0)) - sphere.radius_squared();

    const auto discriminant = b * b - 4 * a * c;

    if (discriminant <= 0) {
        // no intersection if discriminant is < 0
        // tangential to the sphere if the discriminant == 0
        return std::nullopt;
    }

    // ray intersects sphere in two points

    // find the intersection point and the normal vector of the sphere in the intersection point
    const auto t = (-b - std::sqrt(discriminant)) / (a * 2);

    const Point3 intersectionPoint = m_p0 + t * direction();

    const Vec3 normalVector = sphere.normal(intersectionPoint);

    return std::pair { std::move(intersectionPoint), std::move(normalVector) };
}

// ray cube intersection
inline const std::optional<std::pair<const Point3, const Vec3>> Ray::intersect(
    const Cube& cube) const
{

    // TODO:
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

    const Vec3 norm = cube.normal(m_p0);

    double denominator = direction().dot(norm);

    if (denominator <= 1e-6) { // smaller than a very small value (epsilon): no intersection
        return std::nullopt;
    }
    double t = (cube.pos() - m_p0).dot(norm) / denominator;
    if (t < 0) { // plane behind ray's origin
        return std::nullopt;
    }
    const Point3 intersectionPoint = m_p0 + t * direction();
    // std::cout << "CUBE INTERSECTION POINT: " << intersectionPoint << std::endl;
    return std::pair { std::move(intersectionPoint), norm };
}

// ray plane intersection
inline const std::optional<std::pair<const Point3, const Vec3>> Ray::intersect(
    const Plane& plane) const
{
    const Vec3 norm = plane.normal();

    double denominator = direction().dot(norm);

    if (denominator <= 1e-6) { // smaller than a very small value (epsilon): no intersection
        return std::nullopt;
    }
    double t = (plane.pos() - m_p0).dot(norm) / denominator;
    if (t < 0) { // plane behind ray's origin
        return std::nullopt;
    }
    const Point3 intersectionPoint = m_p0 + t * direction();
    // std::cout << "PLANE INTERSECTION POINT: " << intersectionPoint << std::endl;
    return std::pair { std::move(intersectionPoint), norm };
}

// str returns a string representation of the ray.
// The string function returns a constant string ("const std::string"),
// and does not modify anything ("const").
inline const std::string Ray::str() const
{
    std::stringstream ss;
    ss << m_p0 << " -> "s << m_p1;
    return ss.str();
}

// Implement support for the << operator, by calling the Vec3 str method
inline std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.str();
    return os;
}

inline const Vec3 Ray::direction() const { return m_direction; }
