cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE FILEPATH "vcpkg toolchain file")
endif()

project(my_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG QUIET)
find_package(glad CONFIG QUIET)
find_package(glm CONFIG QUIET)

set(MY_ENGINE_BUILD ON)
if(NOT SDL2_FOUND OR NOT glad_FOUND OR NOT glm_FOUND)
    set(MY_ENGINE_BUILD OFF)
    message(WARNING "Dependencies missing (SDL2=${SDL2_FOUND}, glad=${glad_FOUND}, glm=${glm_FOUND}). Skipping build.")
endif()

if(MY_ENGINE_BUILD)
    add_executable(my_engine
        src/main.cpp
        src/core/Game.cpp
        src/core/Window.cpp
        src/gfx/Renderer.cpp
        src/gfx/Shader.cpp
        src/gfx/Mesh.cpp
        src/objects/DotObject.cpp
        src/objects/MarioObject.cpp
        src/objects/TriangleObject.cpp
        src/scene/Scene.cpp
    )

    target_link_libraries(my_engine PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        glad::glad
        glm::glm
    )
endif()
