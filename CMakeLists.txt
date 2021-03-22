cmake_minimum_required(VERSION 3.5)

project(Tetris)

set(SOURCES
    main.cpp 
    tetris.cpp 
)

set(HEADERS 
    tetris.h 
    tetris_const.h 
)

add_executable(tetris ${SOURCES} ${HEADERS} )

set_target_properties(
    tetris PROPERTIES 
    CXX_STANDART 17
    CXX_STANDART_REQUIRED ON
)
# g++ -c main.cpp tetris_const.h
# g++ main.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system