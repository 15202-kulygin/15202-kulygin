cmake_minimum_required(VERSION 3.6)
project(starcraft)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Unit.h BattleCruiser.h BattleCruiser.cpp Zergling.cpp Zergling.h Factory.cpp Factory.h SiegeTank.cpp SiegeTank.h)
add_executable(starcraft ${SOURCE_FILES})