cmake_minimum_required(VERSION 3.29)
project(Proyecto_Videojuegos)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proyecto_Videojuegos
    enemy.cpp
    enemy.h
    game.cpp
    game.h
    main.cpp
    miniwin.cpp
    miniwin.h
    player.cpp
    player.h)

# Enlaza la biblioteca winmm
target_link_libraries(Proyecto_Videojuegos winmm)