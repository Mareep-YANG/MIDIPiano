cmake_minimum_required(VERSION 3.26)
project(MIDIPiano)

set(CMAKE_CXX_STANDARD 17)

add_executable(MIDIPiano src/main.cpp
        src/Entities/Note.cpp
        include/Note.h
        src/Commands/selectCommand.cpp
        src/Commands/startCommand.cpp
        src/Commands/helpCommand.cpp
        src/Logger.cpp
)
target_link_libraries(MIDIPiano PRIVATE winmm)
