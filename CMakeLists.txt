cmake_minimum_required(VERSION 3.26)
project(MIDIPiano)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WIN32_EXECUTABLE ON)
add_executable(MIDIPiano src/main.cpp
        src/Logger.cpp
        src/Entities/NoteEntity.cpp
        src/Commands/SelectCommand.cpp
        src/Commands/StartCommand.cpp
        src/Commands/HelpCommand.cpp

        src/KeyManager.cpp
)


target_link_libraries(MIDIPiano PRIVATE winmm )
