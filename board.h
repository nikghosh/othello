#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include <vector>
#include <limits>
#include "common.h"
#define INF std::numeric_limits<double>::infinity()
using namespace std;

class Board {
   
private:
    bitset<64> black;
    bitset<64> taken;
    bitset<64> corners;
    bitset<64> anticorners;
       
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
      
public:
    Board();
    ~Board();
    Board *copy();
        
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    int countWhiteCorners(); 
    int countBlackCorners();
    double score(Side side);
    vector<Move *> possibleMoves(Side side);
    void setBoard(char data[]);
};

#endif
