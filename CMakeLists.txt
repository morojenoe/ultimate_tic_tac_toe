cmake_minimum_required(VERSION 3.6)
project(strategy)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        position.cpp position.h
        rng.cpp rng.h
        bots/IBot.cpp bots/IBot.h
        bots/RandomBot.cpp bots/RandomBot.h
        RL/IEnvironment.cpp RL/IEnvironment.h
        RL/IAgent.cpp RL/IAgent.h
        RL/ApproximateQAgent.cpp RL/ApproximateQAgent.h
        RL/SimpleExtractor.cpp RL/SimpleExtractor.h
        RL/IFeatureExtractor.cpp RL/IFeatureExtractor.h
        RL/UltimateTicTacToeGame.cpp RL/UltimateTicTacToeGame.h
        bots/RLBot.cpp bots/RLBot.h)

set(STRATEGY_SOURCE_FILES strategy.cpp ${SOURCE_FILES})

add_executable(strategy ${STRATEGY_SOURCE_FILES})


enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests  tests/test_ultimate_tictactoe_game.cpp ${SOURCE_FILES} tests/test_rng.cpp)
target_link_libraries(run_tests ${GTEST_BOTH_LIBRARIES} pthread)
