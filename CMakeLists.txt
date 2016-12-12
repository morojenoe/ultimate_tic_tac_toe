cmake_minimum_required(VERSION 3.6)
project(strategy)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES strategy.cpp
        position.cpp position.h
        rng.cpp rng.h
        IBot.cpp IBot.h
        RandomBot.cpp RandomBot.h)

add_executable(strategy ${SOURCE_FILES})
