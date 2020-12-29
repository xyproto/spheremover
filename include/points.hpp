#pragma once

#include <iomanip>
#include <string>
#include <vector>

using namespace std::string_literals;

using Points = std::vector<Vec3>;

// Implement support for the << operator, by calling the Vec3 str methods
inline std::ostream& operator<<(std::ostream& os, const Points& points)
{
    bool first = true;
    for (auto v : points) {
        if (!first) {
            os << ", "s;
        } else {
            first = false;
        }
        os << v.str();
    }
    return os;
}

// Find the index to the Vec3 in a std::vector<Vec3> that is
// closest to the given point p.
size_t index_closest(const Points xs, const Vec3 p)
{
    size_t smallest_i = 0; // return the first point index, by default
    double smallest_squared_dist = std::numeric_limits<double>::max(); // Largest possible value
    // TODO: Cache the results from distance_squared
    for (size_t i = 0; i < xs.size(); ++i) {
        if (p.distance_squared(xs[i]) < smallest_squared_dist) {
            smallest_squared_dist = p.distance_squared(xs[i]);
            smallest_i = i;
        }
    }
    return smallest_i;
}

// Find the index to the Vec3 in a std::vector<Vec3> that is
// closest to the given point p, except the given indices.
size_t index_closest_except(
    const Points xs, const Vec3 p, const std::vector<size_t> except_indices)
{
    int smallest_i = 0; // return the first point index, by default
    double smallest_squared_dist = std::numeric_limits<double>::max(); // Largest possible value
    // TODO: Cache the results from distance_squared
    for (size_t i = 0; i < xs.size(); ++i) {
        // Thanks Zac Howland at https://stackoverflow.com/a/19299611/131264
        if (std::any_of(std::begin(except_indices), std::end(except_indices),
                [&](size_t i2) { return i2 == i; })) {
            continue;
        }
        if (p.distance_squared(xs[i]) < smallest_squared_dist) {
            smallest_squared_dist = p.distance_squared(xs[i]);
            smallest_i = i;
        }
    }
    return smallest_i;
}
