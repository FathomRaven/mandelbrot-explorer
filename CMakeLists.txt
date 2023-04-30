cmake_minimum_required(VERSION 3.10)

# Define project name and language
project(Mandelbrot CXX)

# Add all source files in src/ to the sources list
file(GLOB SOURCES "src/*.cpp")

# Add all header files in include/ to the headers list
file(GLOB HEADERS "include/*.hpp")

# Add executable target named "Mandelbrot" using the sources list
add_executable(Mandelbrot ${SOURCES} ${HEADERS})

find_package(SDL2 REQUIRED)
target_link_libraries(Mandelbrot PRIVATE SDL2::SDL2)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Mandelbrot PRIVATE Threads::Threads)

# Set target include directories
target_include_directories(Mandelbrot PRIVATE include)