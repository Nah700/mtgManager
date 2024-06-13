cmake_minimum_required(VERSION 3.10)
project(B_OOP_400)
INCLUDE(FindPkgConfig)

add_compile_options(-Wall -Wextra -g -std=c++20)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../lib/")

add_executable(mtgManager main.cpp Core.cpp Graphical.cpp Cards/ACard.cpp GraphicUtils/Button.cpp)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(mtgManager sfml-graphics sfml-window sfml-system sfml-audio jsoncpp curl)

