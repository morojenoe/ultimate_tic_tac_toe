cmake_minimum_required(VERSION 3.6)
project(strategy)

option(tests "Build all tests." ON)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        position.cpp position.h
        rng.cpp rng.h
        bots/IBot.cpp bots/IBot.h
        bots/RandomBot.cpp bots/RandomBot.h
        IEnvironment.cpp IEnvironment.h
        IAgent.cpp IAgent.h
        ApproximateQAgent.cpp ApproximateQAgent.h
        SimpleExtractor.cpp SimpleExtractor.h
        IFeatureExtractor.cpp IFeatureExtractor.h
        UltimateTicTacToeGame.cpp UltimateTicTacToeGame.h
        bots/RLBot.cpp bots/RLBot.h)

set(STRATEGY_SOURCE_FILES strategy.cpp ${SOURCE_FILES})

add_executable(strategy ${STRATEGY_SOURCE_FILES})


enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests  tests/test_ultimate_tictactoe_game.cpp ${SOURCE_FILES} tests/test_rng.cpp)
target_link_libraries(run_tests ${GTEST_BOTH_LIBRARIES} pthread)
