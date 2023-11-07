cmake_minimum_required(VERSION 3.26)
project(MIDIPiano)
set(EasyX_DIR D:/EsayX)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)

link_libraries(libEasyX.a libgdi32.a libole32.a)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WIN32_EXECUTABLE ON)
configure_file("resource/image/background.png" "${CMAKE_BINARY_DIR}/resource/background.png" COPYONLY)
add_executable(MIDIPiano src/main.cpp
        src/Logger.cpp
        src/Entities/NoteEntity.cpp
        src/Commands/SelectCommand.cpp
        src/Commands/StartCommand.cpp
        src/Commands/HelpCommand.cpp

        src/KeyManager.cpp
        src/GuiPiano.cpp
        src/VoiceList.cpp
        src/Commands/RecordCommand.cpp
        src/Entities/MusicNoteEntity.cpp
        src/Entities/MusicEntity.cpp
        src/Commands/MusicPlayCommand.cpp
)


target_link_libraries(MIDIPiano PRIVATE winmm )
