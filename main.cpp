#include <cstdlib>
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "omp.h"

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include "cube.hpp"
#include "disk.hpp"
#include "plane.hpp"
#include "sphere.hpp"

#include "scene.hpp"

#include "script.hpp"

#include "ltimer.h"

#include "sdl2.h"

using namespace std::string_literals;

void TestV2()
{
    std::cout << std::boolalpha;

    Vec2 v2(1.0, 2.0);

    std::cout << "--- V2 ---"s << std::endl;
    std::cout << "v2 " << v2 << std::endl;

    Vec2 a(1.0, 1.1);
    Vec2 b(1.3, 1.4);

    std::cout << a << " + " << b << " = " << a + b << std::endl; // addition
}

void TestV3()
{
    // Output "true" and "false" instead of "1" and "0"
    std::cout << std::boolalpha;

    Vec3 v3(1.0, 2.0, 3.0);

    std::cout << "--- V3 ---"s << std::endl;
    std::cout << "v3 " << v3 << std::endl;

    Vec3 a(1.0, 1.1, 1.2);
    Vec3 b(1.3, 1.4, 1.5);

    std::cout << a << " + " << b << " = " << a + b << std::endl; // addition
    std::cout << a << " - " << b << " = " << a - b << std::endl; // subtraction

    std::cout << a << " * 3.0 = " << a * 3.0 << std::endl; // scale
    std::cout << a << " / 3.0 = " << a / 3.0 << std::endl; // div

    std::cout << a << " dot " << b << " = " << a.dot(b) << std::endl; // dot product
    std::cout << a << " cross " << b << " = " << a.cross(b) << std::endl; // cross product

    std::cout << "normalized version of " << a << " = " << a.normalize() << std::endl; // length

    std::cout << "len of " << a << " = " << a.len() << std::endl; // length
    std::cout << "len of " << b << " = " << b.len() << std::endl; // length

    std::cout << a << " < " << b << "? " << (a < b) << std::endl;
    std::cout << a << " > " << b << "? " << (a > b) << std::endl;
}

void TestV4()
{
    // Output "true" and "false" instead of "1" and "0"
    std::cout << std::boolalpha;

    Vec4 v4(1.0, 2.0, 3.0, 4.0);

    std::cout << "--- V4 ---"s << std::endl;
    std::cout << "v4 " << v4 << std::endl;

    Vec4 a(1.0, 1.1, 1.2, 1.3);
    Vec4 b(1.3, 1.4, 1.5, 1.6);

    std::cout << a << " + " << b << " = " << a + b << std::endl; // addition
    std::cout << a << " - " << b << " = " << a - b << std::endl; // subtraction

    std::cout << a << " * 3.0 = " << a * 3.0 << std::endl; // scale
    std::cout << a << " / 3.0 = " << a / 3.0 << std::endl; // div

    std::cout << a << " dot " << b << " = " << a.dot(b) << std::endl; // dot product

    // There are not cross products for R^4, only R^3 and R^7
    // std::cout << a << " cross " << b << " = " << a.cross(b) << std::endl; // cross product

    std::cout << "normalized version of " << a << " = " << a.normalize() << std::endl; // length

    std::cout << "len of " << a << " = " << a.len() << std::endl; // length
    std::cout << "len of " << b << " = " << b.len() << std::endl; // length

    std::cout << a << " < " << b << "? " << (a < b) << std::endl;
    std::cout << a << " > " << b << "? " << (a > b) << std::endl;
}

void TestSphere()
{
    std::cout << std::boolalpha;

    std::cout << "--- Sphere ---"s << std::endl;

    Sphere s1 { 1.0, 2.0, 3.0, 4.0 };
    Vec3 pos { 0.1, 0.2, 0.3 };
    Sphere s2 { pos, 5.0 };

    std::cout << "Sphere 1 "s << s1 << std::endl;
    std::cout << "Sphere 2 "s << s2 << std::endl;
}

void TestCube()
{
    std::cout << std::boolalpha;

    std::cout << "--- Cube ---"s << std::endl;

    Cube c1 { 1.0, 2.0, 3.0, 1.0, 1.0, 1.0 };
    Vec3 pos { 0.1, 0.2, 0.3 };

    std::cout << "Cube 1: "s << c1 << std::endl;

    Cube c2 { 0.5, 0.5, 0.5, 1.0 };
    std::cout << "Cube 2: "s << c2 << std::endl;
    std::cout << "Cube 2 point methods:"s << std::endl;
    std::cout << "\t" << c2.p0() << std::endl;
    std::cout << "\t" << c2.p1() << std::endl;
    std::cout << "\t" << c2.p2() << std::endl;
    std::cout << "\t" << c2.p3() << std::endl;
    std::cout << "\t" << c2.p4() << std::endl;
    std::cout << "\t" << c2.p5() << std::endl;
    std::cout << "\t" << c2.p6() << std::endl;
    std::cout << "\t" << c2.p7() << std::endl;
    std::cout << "Cube 2 points: "s << c2.points() << std::endl;
}

void TestDisk()
{
    std::cout << std::boolalpha;

    std::cout << "--- Disk ---"s << std::endl;

    Disk c1 { 1.0, 2.0, 3.0, 5.0 };

    std::cout << "Disk 1: "s << c1 << std::endl;
}

void TestPlane()
{
    std::cout << std::boolalpha;

    std::cout << "--- Plane ---"s << std::endl;

    Plane p1 { Point3 { 1.0, 2.0, 3.0 }, Vec3 { 0, 5.0, 0 } };

    std::cout << "Plane 1: "s << p1 << std::endl;
}

void TestRay()
{
    std::cout << std::boolalpha;

    std::cout << "--- Ray ---"s << std::endl;

    Vec3 pos0 { 0.1, 0.2, 0.3 };
    Vec3 pos1 { 0.1, 0.2, 0.3 };

    Ray ray { pos0, pos1 };

    std::cout << "Ray: " << ray << std::endl;

    Sphere s1 { 1.0, 2.0, 3.0, 4.0 };

    std::cout << "Sphere: " << s1 << std::endl;

    // intersect returns an optional pair of the intersection point and normal from
    // the intersection point on the sphere
    if (auto maybeIntersectionPoint = ray.intersect(s1)) {
        const auto intersectionPointAndNormal = maybeIntersectionPoint.value();
        const auto intersectionPoint = intersectionPointAndNormal.first;
        const auto intersectionPointNormal = intersectionPointAndNormal.second;
        std::cout << "Ray intersects sphere at " << intersectionPoint << std::endl;
        std::cout << "Ray has normal at intersection point " << intersectionPointNormal
                  << std::endl;
    } else {
        std::cout << "Ray does not intersect the sphere." << std::endl;
    }
}

auto TestSDL2RayTrace() -> int
{

    using std::cerr;
    using std::endl;

    auto sys = sdl2::make_sdlsystem(SDL_INIT_EVERYTHING);
    if (!sys) {
        cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
        return 1;
    }

    // Select if fullscreen should be default here
    bool fullscreen = false;

    // This is the resolution of what's drawn in the window, regardless of the window resolution
    const int W = 495;
    const int H = 270;

    int winw;
    int winh;
    int winf;

    if (fullscreen) {
        winw = 0;
        winh = 0;
        winf = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else {
        winw = 1980;
        winh = 1080;
        winf = SDL_WINDOW_SHOWN;
    }

    auto win = sdl2::make_window("Sphere Mover", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winw, winh, winf);
    if (!win) {
        cerr << "Error creating window: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_ShowCursor(!fullscreen);

    auto ren = sdl2::make_renderer(win.get(), -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        cerr << "Error creating renderer: " << SDL_GetError() << endl;
        return 1;
    }

    auto tex = sdl2::make_buffer_texture(ren.get(), W, H);
    if (!tex) {
        cerr << "Error creating texture: " << SDL_GetError() << endl;
        return 1;
    }

    uint32_t* textureBuffer = new uint32_t[W * H];

    const Sphere light { Vec3 { 0, 0, 50 }, 1 };
    const Plane plane { Vec3 { 0, 0, 100 }, (Vec3 { 0, 0, 0.5 }).normalize() };

    const Sphere sphere1 { Vec3 { W * .4, H * .5, 50 }, 50 };
    const Sphere sphere2 { Vec3 { W * .5, H * .5, 50 }, 50 };
    const Sphere sphere3 { Vec3 { W * .6, H * .5, 50 }, 50 };

    std::vector<Sphere> spheres = { sphere1, sphere2, sphere3 };

    // Create a scene and a scene pointer
    Scene scene1 { light, plane, spheres, Color::darkgray };
    std::unique_ptr<Scene> scene_ptr = std::make_unique<Scene>(scene1);

    // Create a camera point
    const Point3 fromPoint { 0, 0, -W * 2 };

    // Select a sphere by switching between them with the Tab key
    size_t currentSphere = 0;

    SDL_Event event;

    std::cout << "arrow keys and tab to move spheres around" << std::endl;
    std::cout << "esc or q to quit" << std::endl;
    std::cout << "f to toggle fullscreen" << std::endl;

    bool quit = false;

    // Thanks: https://lazyfoo.net/tutorials/SDL/25_capping_frame_rate/
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    LTimer fpsTimer;
    LTimer capTimer;
    int countedFrames = 0;
    fpsTimer.start();

    while (!quit) {

        capTimer.start();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                case SDLK_TAB: {
                    //std::cout << "Tab" << std::endl;
                    currentSphere++;
                    if (currentSphere >= spheres.size()) {
                        currentSphere = 0;
                    }
                    break;
                }
                case SDLK_d:
                case SDLK_RIGHT: {
                    //std::cout << "Right" << std::endl;
                    const auto newScene = scene_ptr->sphere_move(currentSphere, Vec3 { 1, 0, 0 });
                    scene_ptr = std::make_unique<Scene>(newScene);
                    break;
                }
                case SDLK_a:
                case SDLK_LEFT: {
                    //std::cout << "Left" << std::endl;
                    const auto newScene = scene_ptr->sphere_move(currentSphere, Vec3 { -1, 0, 0 });
                    scene_ptr = std::make_unique<Scene>(newScene);
                    break;
                }
                case SDLK_w:
                case SDLK_UP: {
                    //std::cout << "Up" << std::endl;
                    const auto newScene = scene_ptr->sphere_move(currentSphere, Vec3 { 0, -1, 0 });
                    scene_ptr = std::make_unique<Scene>(newScene);
                    break;
                }
                case SDLK_s:
                case SDLK_DOWN: {
                    //std::cout << "Down" << std::endl;
                    const auto newScene = scene_ptr->sphere_move(currentSphere, Vec3 { 0, 1, 0 });
                    scene_ptr = std::make_unique<Scene>(newScene);
                    break;
                }
                case SDLK_f:
                    // TODO: Also check SDL_GetWindowFlags(win) & SDL_WINDOWS_FULLSCREEN?
                    if (fullscreen) {
                        SDL_SetWindowFullscreen(win.get(), 0);
                        SDL_ShowCursor(true);
                        fullscreen = false;
                    } else {
                        SDL_SetWindowFullscreen(win.get(), SDL_WINDOW_FULLSCREEN);
                        SDL_ShowCursor(false);
                        fullscreen = true;
                    }
                    break;
                case SDLK_q:
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        double avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.0);
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }

// Use OpenMP
#pragma omp parallel for
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                //if (x % 2 != 0) {
                //    textureBuffer[(y * W) + x] = textureBuffer[(y * W) + x - 1];
                //} else {
                const RGB c = scene_ptr->color(fromPoint, x, y).clamp255();
                textureBuffer[(y * W) + x] = 0xFF000000 | (static_cast<uint8_t>(c.R()) << 16) | (static_cast<uint8_t>(c.B()) << 8) | static_cast<uint8_t>(c.G());
                //}
            }
        }

        SDL_UpdateTexture(tex.get(), nullptr, textureBuffer, W * sizeof(uint32_t));

        SDL_RenderClear(ren.get());
        SDL_RenderCopy(ren.get(), tex.get(), nullptr, nullptr);
        SDL_RenderPresent(ren.get());

        ++countedFrames;

        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }
    SDL_Quit();
    return 0;
}

void TestRayTrace(const std::string filename)
{
    const int W = 320;
    const int H = 200;

    const Sphere light { Vec3 { 0, 0, 50 }, 1 };
    const Plane plane { Vec3 { 0, 0, 100 }, (Vec3 { 0, 0, 0.5 }).normalize() };

    const Sphere sphere1 { Vec3 { W * .4, H * .5, 50 }, 50 };
    const Sphere sphere2 { Vec3 { W * .5, H * .5, 50 }, 50 };
    const Sphere sphere3 { Vec3 { W * .6, H * .5, 50 }, 50 };

    std::vector<Sphere> spheres = { sphere1, sphere2, sphere3 };

    std::ofstream out(filename);
    out << "P3\n"s << W << " "s << H << " "s
        << "255\n"s;

    // Create a scene
    Scene scene { light, plane, spheres, Color::darkgray };

    // Create a camera point
    const Point3 fromPoint { 0, 0, -W * 2 };

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            out << scene.color(fromPoint, x, y).clamp255().ppm() << "\n";
        }
    }
}

// mustRead reads the contents of the given filename,
// with no error checking except possibly exceptions
auto mustRead(const std::string filename) -> const std::string
{
    std::stringstream buf;
    std::ifstream f { filename };
    buf << f.rdbuf();
    return buf.str();
}

auto TestScript(const std::string filename) -> int
{
    std::cout << "--- SCRIPT: " << filename << " ---" << std::endl;
    const std::string source = mustRead(filename);
    std::cout << "read " << source.length() << " characters" << std::endl;
    return interpret(tokenize(source));
}

auto main() -> int
{
    /*TestV2();
    TestV3();
    TestV4();

    TestSphere();
    TestCube();
    TestDisk();
    TestPlane();

    TestRay();
    TestRayTrace("/tmp/out.ppm"s);

    TestScript(SCRIPTDIR "hello.pip"s);
    TestScript(SCRIPTDIR "hello2.pip"s);*/

    TestSDL2RayTrace();

    return EXIT_SUCCESS;
}
