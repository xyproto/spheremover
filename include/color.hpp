#pragma once

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

using RG = Vec2;
using RGB = Vec3;
using RGBA = Vec4;

namespace Color {

const RGB red = RGB { 255, 0, 0 };
const RGB green = RGB { 0, 255, 0 };
const RGB blue = RGB { 0, 0, 255 };

const RGB black = RGB { 0, 0, 0 };
const RGB white = RGB { 255, 255, 255 };

const RGB blueish { 80, 140, 255 };
const RGB gray { 128, 128, 128 };

const RGB darkgray { 32, 32, 32 };

}
