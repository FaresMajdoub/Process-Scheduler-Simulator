cmake_minimum_required(VERSION 3.29)
project(tp1-ordonnancement-CollectorsObservatory)

set(CMAKE_CXX_STANDARD 20)

add_executable(tp1-ordonnancement-CollectorsObservatory simulateur.cpp
        processus.h
        processus.cpp
        ordonnanceur.h
        ordonnanceur.cpp
        ContratException.cpp
        ContratException.h)