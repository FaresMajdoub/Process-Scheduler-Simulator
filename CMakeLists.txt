cmake_minimum_required(VERSION 3.29)
project(Process-Scheduler-Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Process-Scheduler-Simulator
 simulateur.cpp
        processus.h
        processus.cpp
        ordonnanceur.h
        ordonnanceur.cpp
        ContratException.cpp
        ContratException.h)
