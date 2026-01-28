cmake_minimum_required(VERSION 3.21)
project(my_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_engine
    src/main.cpp
    src/core/Window.cpp
    src/gfx/Shader.cpp
    src/gfx/Mesh.cpp
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(my_engine PRIVATE
  SDL2::SDL2
  SDL2::SDL2main
  glad::glad
  glm::glm
)
project(my_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_engine
    src/main.cpp
    src/core/Window.cpp
    src/gfx/Shader.cpp
    src/gfx/Mesh.cpp
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(my_engine PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    glad::glad
    glm::gl
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

if(TARGET ${MY_ENGINE_TARGET})
  target_link_libraries(${MY_ENGINE_TARGET} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    glad::glad
    glm::glm
  )
endif()
