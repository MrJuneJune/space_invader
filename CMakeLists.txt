cmake_minimum_required(VERSION 3.10)

# Export compile commands (useful for LSP tools)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_OSX_ARCHITECTURES "arm64")

project(space_invader VERSION 0.5
  DESCRIPTION "Space Invader"
  LANGUAGES CXX)

set(SOURCES
    src/main.cpp
)

# Add an executable target first
add_executable(space_invader ${SOURCES})

# set the include and library paths manually because cmake can't find this.
set(raylib_INCLUDE_DIR /home/linuxbrew/.linuxbrew/opt/raylib/include)
set(raylib_LIBRARY /home/linuxbrew/.linuxbrew/opt/raylib/lib/libraylib.a)

# Include raylib headers
include_directories(${raylib_INCLUDE_DIR})

## Graphics
find_package(raylib REQUIRED)

# Link raylib library after the executable target is created
target_link_libraries(space_invader PRIVATE ${raylib_LIBRARY})

