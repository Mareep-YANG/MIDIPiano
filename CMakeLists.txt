cmake_minimum_required(VERSION 3.26)
project(MIDIPiano)

set(CMAKE_CXX_STANDARD 17)

add_executable(MIDIPiano src/main.cpp
)
target_link_libraries(MIDIPiano PRIVATE winmm)
