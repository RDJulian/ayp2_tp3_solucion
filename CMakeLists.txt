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
        src/Grafo.cpp
        src/Floyd.cpp
        src/Dijkstra.cpp
        src/Matriz.cpp
        src/ConversorTablero.cpp
        src/Tablero.cpp
        src/Visual.cpp
        include/ABB.hpp
        include/NodoABB.hpp
        include/Heap.hpp
        include/color.hpp
        main.cpp
        src/Random.cpp
        include/Random.hpp
        src/GeneradorTablero.cpp
        include/GeneradorTablero.hpp
        src/InventarioArmas.cpp
        include/InventarioArmas.hpp
        src/ArbolPlacas.cpp
        include/ArbolPlacas.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")