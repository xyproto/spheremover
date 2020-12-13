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
