#include "player.h"
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->side = side;
    opp_side = (side == WHITE) ? BLACK : WHITE;
    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

void Player::setBoard(Board *b) {
    board = b;
}

int Player::minimax(Board *b, int depth, bool max_player) {
    if(depth == 0)
        return b->score(side);

    int best_score;

    if(max_player) {
        best_score = -INF;
        vector<Move *> moves = b->possibleMoves(side);
        for(auto &m : moves) {
            Board *child = b->copy();
            child->doMove(m, side);
            int v = minimax(child, depth - 1, false);
            best_score = max(best_score, v);
        }
    }
    else {
        best_score = INF;
        vector<Move *> moves = b->possibleMoves(opp_side);
        for(auto &m : moves) {
            Board *child = b->copy();
            child->doMove(m, opp_side);
            int v = minimax(child, depth - 1, true);
            best_score = min(best_score, v);
        }
    }

    return best_score;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    
    board->doMove(opponentsMove, opp_side);
    vector<Move *> moves = board->possibleMoves(side);
    if(moves.empty())
        return NULL;

    int max_score, best_move = 0;

     for(int i = 0; i < moves.size(); i++) {
        Board *next = board->copy();
        next->doMove(moves[i], side);
        int s = minimax(next, 3, false);
        if(i == 0)
            max_score = s;
        else if(s > max_score) {
            max_score = s;
            best_move = i;
        }
    }

    board->doMove(moves[best_move], side);
    return moves[best_move];
}
