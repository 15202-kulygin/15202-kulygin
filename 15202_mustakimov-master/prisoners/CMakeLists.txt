cmake_minimum_required(VERSION 3.6)
project(prisoners)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Strategy.cpp
        Strategies/Traitor.cpp
        Strategies/Loyal.cpp
        Controller.cpp
        ScoreMatrix.cpp
        Strategies/Random.cpp
        Strategies/Revengeful.cpp
        Strategies/Varying.cpp
        Arguments.cpp
        Strategies/Democracy.cpp
        Strategies/Psycologist.cpp ControllerFast.cpp ControllerFast.h ControllerDetailed.cpp ControllerDetailed.h ControllerTournament.cpp ControllerTournament.h)

add_executable(prisoners
        main.cpp
        ${SOURCE_FILES})

add_subdirectory(Tests)