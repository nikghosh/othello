#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {
private:
	Board *board;
	Side side;
	Side opp_side;

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    double minimax(Board *b, int depth, bool max_player);
    double alphabeta(Board *b, int depth, double alpha, double beta, bool max_player);
    void setBoard(Board *b);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
