#!/usr/bin/env bash

g++ -std=c++1y -O2 -static -lm -Isrc strategy.cpp position.cpp position.h rng.cpp rng.h bots/IBot.cpp bots/IBot.h bots/RandomBot.cpp bots/RandomBot.h IEnvironment.cpp IEnvironment.h IAgent.cpp IAgent.h ApproximateQAgent.cpp ApproximateQAgent.h SimpleExtractor.cpp SimpleExtractor.h IFeatureExtractor.cpp IFeatureExtractor.h UltimateTicTacToeGame.cpp UltimateTicTacToeGame.h bots/RLBot.cpp bots/RLBot.h
java -cp ../ultimatetictactoe-engine/bin com.theaigames.tictactoe.Tictactoe "./a.out" "./random_bot.out" 2>err.txt 1>out.txt
