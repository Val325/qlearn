cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_COMPILER "/bin/clang++")
project(qlearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(Libs ${PROJECT_SOURCE_DIR}/lib)
message("path: ${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath lib -lSDL2_ttf -lSDL2_mixer -L lib -fsanitize=address")

include_directories(${PROJECT_SOURCE_DIR}/inc)
find_library(SDL2 NAMES SDL2 PATHS ${PROJECT_SOURCE_DIR}/lib)

add_executable(qlearn src/main.cpp)
target_link_libraries(qlearn SDL2)
