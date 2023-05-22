#include "Node.hpp"

#include <iostream>
#include <vector>

using namespace std;

#ifndef _Ant_h_
#define _Ant_h_

class Ant
{
private:


public:

    Ant();
    Ant(Node startPoint);
    ~Ant();

    vector <Node> path;
    int id;

    int getLastNodeId();
    int* getLastNodeIndex(int* index);
    int* getPenultimate(int* index);
    void insertNewNode(Node newOne);
    int getPathSize();

};

#endif
