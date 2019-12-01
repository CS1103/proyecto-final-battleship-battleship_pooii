cmake_minimum_required(VERSION 3.13.4)
project(proyecto-final-battleship-battleship_pooii)

# Archivos del Projecto
set(PROJECT_SOURCE
        src/main.cpp src/funct.cpp src/ship.cpp src/tablero.cpp src/casillas.cpp src/Player.hpp)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "~/DevLibraries/SFML-2.5.1-macOS-clang")

set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

# Apple
set(SFML_DIR "${SFML_ROOT}/Frameworks/SFML.framework/Resources/CMake")

link_directories(${SFML_LIBRARY_DIR})
include_directories(${SFML_INCLUDE_DIR})

# Instrucciones para generar el ejecutable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

find_package(SFML 2.5.1
        COMPONENTS
        system
        window
        graphics
        REQUIRED)

target_link_libraries (${PROJECT_NAME}
        sfml-system
        sfml-window
        sfml-graphics
        )
