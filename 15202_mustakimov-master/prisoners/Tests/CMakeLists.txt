project(tests)

add_subdirectory(../../gtest gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES
        ../Strategy.cpp
        ../Strategies/Traitor.cpp
        ../Strategies/Loyal.cpp
        ../Controller.cpp
        ../ScoreMatrix.cpp
        ../Strategies/Random.cpp
        ../Strategies/Revengeful.cpp
        ../Strategies/Varying.cpp
        ../Arguments.cpp
        ../Strategies/Democracy.cpp
        ../Strategies/Psycologist.cpp ../ControllerFast.cpp ../ControllerFast.h ../ControllerTournament.cpp ../ControllerTournament.h)

add_executable(runTests
        FactoryTest.cpp
        ${SOURCE_FILES})

target_link_libraries(runTests gtest gtest_main)