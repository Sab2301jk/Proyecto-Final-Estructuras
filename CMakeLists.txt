cmake_minimum_required(VERSION 4.3)
project(Proyecto_final_Urgencias)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_final_Urgencias main.cpp
        Medico.cpp
        Medico.h
        Simulador.cpp
        Simulador.h
        HistorialHash.cpp
        HistorialHash.h
        CamaCorredor.cpp
        CamaCorredor.h
        NodoCama.cpp
        NodoCama.h
        Paciente.cpp
        Paciente.h
)
