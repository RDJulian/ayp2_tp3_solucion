cmake_minimum_required(VERSION 3.22)
project(ayp2_tp3_solucion)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Werror -Wconversion)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CXXFLAGS "-Wall -Werror -Wconversion")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

include_directories(include)
include_directories(src)

add_executable(ayp2_tp3_solucion
        src/Placa.cpp
        src/Arma.cpp
        src/TDAs/Grafo/Grafo.cpp
        src/TDAs/Grafo/Floyd.cpp
        src/TDAs/Grafo/Dijkstra.cpp
        src/TDAs/Matriz.cpp
        src/ConversorTablero.cpp
        src/Tablero.cpp
        src/Visual.cpp
        src/Random.cpp
        src/GeneradorTablero.cpp
        src/InventarioArmas.cpp
        src/ArbolPlacas.cpp
        src/Casillero.cpp
        src/Simulador.cpp
        src/Camino.cpp
        include/TDAs/ABB.hpp
        include/TDAs/NodoABB.hpp
        include/TDAs/Heap.hpp
        main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")