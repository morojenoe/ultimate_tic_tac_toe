cmake_minimum_required(VERSION 3.6)
project(strategy)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES strategy.cpp
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

add_executable(strategy ${SOURCE_FILES})
