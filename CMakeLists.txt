cmake_minimum_required(VERSION 3.14)
project(KeyGen)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "/usr/include/SFML")
set(SFML_LIBRARY_DIR "/usr/lib/SFML")

link_directories (SFML_LIBRARY_DIR)
include_directories (SFML_INCLUDE_DIR)

add_executable(KeyGen main.cpp Visual/objects/ClassCat.cpp
                                Visual/Controller.cpp
        Visual/Engines/PhysicEngine.cpp
        Visual/Templates/PhysMove.cpp
        Visual/Templates/SpriteAnimation.cpp
        Visual/Engines/UserControlEngine.cpp
        Visual/Templates/UserCtrlMove.cpp
        Visual/Templates/VisMove.cpp
        Visual/Engines/VisualEngine.cpp

        Visual/Engines/Engines.hpp
        Visual/objects/ClassCat.hpp
                                Visual/Controller.hpp
        Visual/Engines/PhysicEngine.hpp
        Visual/Templates/PhysMove.hpp
        Visual/Templates/SpriteAnimation.hpp
        Visual/Engines/UserControlEngine.hpp
        Visual/Templates/UserCtrlMove.hpp
        Visual/Templates/VisMove.hpp
        Visual/Engines/VisualEngine.hpp hack_lib.cpp hack_lib.h Visual/objects/file_box.cpp Visual/objects/file_box.hpp Visual/objects/Objects.hpp Visual/objects/Objects.cpp Visual/objects/hack_box.cpp Visual/objects/hack_box.hpp)

target_link_libraries (KeyGen sfml-graphics sfml-window sfml-system sfml-audio)
