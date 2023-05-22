#include "GridSystem.hpp"

#ifndef _Node_h_
#define _Node_h_

class Node
{
private:
    int row;        //arrayIndex +1
    int column;
    int id;
    void calculateId(int width);

  
public:
    Node();
    Node(int arrayIndex_c, int arrayIndex_r, int width);
    ~Node();

    double tempProb;    //variable to help to calculate the probability
    double prob;        //probability from current to this
    double isDiagonal;
    

    int getId();
    int getRow();
    int getColumn();

};

#endif