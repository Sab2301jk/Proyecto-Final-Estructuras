cmake_minimum_required(VERSION 4.1)
project(proyectoFinalED)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyectoFinalED main.cpp
        Paciente.cpp
        Paciente.h
        HistorialHash.cpp
        HistorialHash.h)
