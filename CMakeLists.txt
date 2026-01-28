cmake_minimum_required(VERSION 3.21)
project(my_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MY_ENGINE_TARGET my_engine)
if(NOT TARGET ${MY_ENGINE_TARGET})
  add_executable(${MY_ENGINE_TARGET}
    src/main.cpp
  )
endif()

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
