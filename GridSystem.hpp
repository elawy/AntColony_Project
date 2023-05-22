
#ifndef _GridSystem_h_
#define _GridSystem_h_

#include <iostream>
using namespace std;

class GridSystem
{
 
private:
    int startIndex [2];       //{coloum, row}
    int endIndex [2];

public:
    GridSystem();
    ~GridSystem();

    int height;
    int width;

    void setDimesions(int hight,  int width);
    void setStart(int y, int x);
    void setEnd(int y, int x);

    char* grid;
    int* getStartIndex();
    int* getEndIndex();

    bool checkIfObstacleBorder(int column, int row);

    void setGrid(int y, int x, char value);
    char getGrid(int y, int x);


    char* initializeGrid();

};



#endif
