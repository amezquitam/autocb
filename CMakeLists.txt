cmake_minimum_required(VERSION 3.25)

# set(CMAKE_CXX_STANDARD 17)

project(autocb)

add_executable(autocb src/main.cpp src/trigonometric.cpp)
# target_link_options(autocb PUBLIC "-static")

# add_executable(autocb_test test/catch.cpp test/test.cpp src/trigonometric.cpp)
# target_include_directories(autocb_test PUBLIC src)