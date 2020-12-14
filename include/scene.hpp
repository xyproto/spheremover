#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "color.hpp"
#include "point.hpp"
#include "vec3.hpp"

#include "ray.hpp"

#include "disk.hpp"
#include "plane.hpp"
#include "sphere.hpp"

using namespace std::string_literals;

// Sphere has a position and a radius
class Scene {
protected:
    Sphere m_light;
    std::vector<Plane> m_planes;
    std::vector<Sphere> m_spheres;
    RGB m_backgroundColor;

public:
    Scene(Sphere light, Plane plane, Sphere sphere, RGB backgroundColor)
        : m_light { light }
        , m_backgroundColor { backgroundColor }
    {
        m_planes.push_back(plane);
        m_spheres.push_back(sphere);
    }

    Scene(Sphere light, Plane plane, std::vector<Sphere> spheres, RGB backgroundColor)
        : m_light { light }
        , m_spheres { spheres }
        , m_backgroundColor { backgroundColor }
    {
        m_planes.push_back(plane);
    }

    Scene(
        Sphere light, std::vector<Plane> planes, std::vector<Sphere> spheres, RGB backgroundColor)
        : m_light { light }
        , m_planes { planes }
        , m_spheres { spheres }
        , m_backgroundColor { backgroundColor }
    {
    }

    const std::string str() const;
    const RGB color(const Point3 fromPoint, int x, int y) const;

    // Methods for modifying the scene by creating an entirely new scene
    const Scene light_move(const Vec3 offset) const;
    const Scene sphere_move(const size_t index, const Vec3 offset) const;
};

// Move a sphere by creating an enitirely new scene
const Scene Scene::sphere_move(const size_t index, const Vec3 offset) const
{
    if (m_spheres.empty()) {
        return Scene { m_light, m_planes, m_spheres, m_backgroundColor };
    }

    std::vector<Sphere> newSpheres;
    for (size_t i = 0; i < m_spheres.size(); ++i) {
        if (i == index) {
            const auto newPos = m_spheres[i].pos() + offset;
            const auto newRadius = m_spheres[i].r();
            Sphere newSphere = Sphere { newPos, newRadius };
            newSpheres.push_back(newSphere);
        } else {
            newSpheres.push_back(m_spheres[i]);
        }
    }
    return Scene { m_light, m_planes, newSpheres, m_backgroundColor };
}

// Move the light by creating an enitirely new scene
const Scene Scene::light_move(const Vec3 offset) const
{
    auto newPos = m_light.pos() + offset;
    auto newRadius = m_light.r();
    Sphere newLight = Sphere { newPos, newRadius };
    return Scene { newLight, m_planes, m_spheres, m_backgroundColor };
}

// List the elements in this scene
inline const std::string Scene::str() const
{
    std::stringstream ss;
    ss << "background color: " << m_backgroundColor << "\n";
    ss << "light: " << m_light << "\n";
    for (const auto sphere : m_spheres) {
        ss << sphere << "\n";
    }
    for (const auto plane : m_planes) {
        ss << plane << "\n";
    }
    return ss.str();
}

// Implement support for the << operator, by calling the Scene str method
inline std::ostream& operator<<(std::ostream& os, const Scene& s)
{
    os << s.str();
    return os;
}

// Raytrace for a single pixel
inline const RGB Scene::color(const Point3 fromPoint, int x, int y) const
{

    std::unordered_map<double, RGB> depthColor;

    // Create a new ray, going from fromPoint towards (x,y,0)
    const auto ray = Ray { fromPoint, Vec3 { static_cast<double>(x), static_cast<double>(y), 0 } };

    // TODO: Loop over an object type instead of spheres and planes. They can inherent from object.

    double smallestDepth = 0;
    bool firstFind = true;

    for (const auto sphere : m_spheres) {

        // Check if the ray intersects with the sphere, and deal with the optional returns
        if (const auto maybeIntersectionPointAndNormal = ray.intersect(sphere)) {

            // Retrieve the intersection point and normal as a pair
            const auto intersectionPointAndNormal = maybeIntersectionPointAndNormal.value();

            // Pick out the intersection point and the normal. The normal from the sphere is
            // sometimes known as just "N".
            const Point3 intersectionPoint = intersectionPointAndNormal.first;
            const Vec3 normal = intersectionPointAndNormal.second;

            // Get the vector pointing to the light from the intersection point. This is
            // sometimes known as just "L".
            const auto lightDirection = m_light.pos() - intersectionPoint;

            // Get the dot product between the normalized light vector and the normalized
            // normal vector. This says something about to which degree the surface normal
            // points towards the light.
            const double dt = lightDirection.normalize().dot(normal.normalize());

            // Use a formula for producting a color from dt.
            RGB currentColor = (Color::red + Color::white * dt) * .5;

            // TODO: Optimize by using distancedistance instead of distance, to avoid a sqrt?
            double depth = fromPoint.distance(intersectionPoint);

            if (depth < smallestDepth || firstFind) {
                smallestDepth = depth;
                firstFind = false;
            }

            depthColor.insert(
                std::make_pair<double, RGB>(std::move(depth), std::move(currentColor)));

            // Clamp the color values to the 0..255 range
            // return currentColor.clamp255();
        }
    }

    for (const auto plane : m_planes) {

        // Check if the ray intersects with the sphere, and deal with the optional returns
        if (const auto maybeIntersectionPointAndNormal = ray.intersect(plane)) {

            // Retrieve the intersection point and normal as a pair
            const auto intersectionPointAndNormal = maybeIntersectionPointAndNormal.value();

            // Pick out the intersection point and the normal. The normal from the plane is
            // sometimes known as just "N".
            const Point3 intersectionPoint = intersectionPointAndNormal.first;
            const Vec3 normal = intersectionPointAndNormal.second;

            // Get the vector pointing to the light from the intersection point. This is
            // sometimes known as just "L".
            const auto lightDirection = m_light.pos() - intersectionPoint;

            // Get the dot product between the normalized light vector and the normalized
            // normal vector. This says something about to which degree the surface normal
            // points towards the light.
            const double dt = lightDirection.normalize().dot(normal.normalize());

            // Use a formula for producting a color from dt.
            RGB currentColor
                = ((Color::blueish + Color::white * dt) * .5) * .5 + m_backgroundColor * .5;

            // TODO: Optimize by using distancedistance instead of distance, to avoid a sqrt?
            double depth = fromPoint.distance(intersectionPoint);

            if (depth < smallestDepth || firstFind) {
                smallestDepth = depth;
                firstFind = false;
            }

            depthColor.insert(
                std::make_pair<double, RGB>(std::move(depth), std::move(currentColor)));

            // Clamp the color values to the 0..255 range
            // return currentColor.clamp255();
        }
    }

    if (firstFind) { // Found no color to use
        return m_backgroundColor;
    }

    // Now return the color that had the smallest depth, clamped to the 0..255 range
    RGB closestColor = depthColor.at(smallestDepth);
    return closestColor.clamp255();
}
