cmake_minimum_required(VERSION 3.12)
project(spheremover)

# OS-specific configurations
if(APPLE)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
    endif()
else()
    # Linux-specific compiler settings
    set(CMAKE_CXX_COMPILER g++)
    set(CMAKE_C_COMPILER gcc)
endif()

# Find required packages
find_package(SDL2 REQUIRED)
find_package(OpenMP REQUIRED)

# Define source files
set(SOURCES main.cpp common/script.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set C++ and C standards
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 18)

# Set compiler flags based on OS
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -std=c++23 -O3 -Wall -Wshadow -Wpedantic -Wno-parentheses -Wvla -Wignored-qualifiers -Wno-unqualified-std-cast-call")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -O3 -pipe -fPIC -fno-plt -fstack-protector-strong -fopenmp -Wall -Wshadow -Wpedantic -Wno-parentheses -Wvla -Wignored-qualifiers -Wno-unqualified-std-cast-call")
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    .
    ..
    ${SDL2_INCLUDE_DIRS}
    common
    include
)

# Link libraries based on OS
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARIES}
        OpenMP::OpenMP_CXX
        "-framework OpenGL"
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARIES}
        OpenMP::OpenMP_CXX
        dl
        pthread
    )
    # Linux-specific link flags
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-fopenmp -pthread -Wl,--as-needed"
    )
endif()

# Define macros
add_definitions(
    -DIMGDIR="${CMAKE_CURRENT_SOURCE_DIR}/img/"
    -DSCRIPTDIR="${CMAKE_CURRENT_SOURCE_DIR}/scripts/"
    -D_REENTRANT
)