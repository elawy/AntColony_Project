#include "GridSystem.hpp"

GridSystem::GridSystem()
{
}

GridSystem::~GridSystem()
{
    free(grid);
}

void GridSystem::setDimesions(int setHight,  int setWidth)
{
    height = setHight;
    width = setWidth;
}

void GridSystem::setStart(int y, int x){
    this->startIndex[0] = x;
    this->startIndex[1] = y;
}


void GridSystem::setEnd(int y, int x){
    this->endIndex[0] = x;
    this->endIndex[1] = y;
}




int* GridSystem::getStartIndex(){
    return startIndex;
}

int* GridSystem::getEndIndex(){
    return endIndex;
}

bool GridSystem::checkIfObstacleBorder(int column, int row){
    if ( (column >= width) || (column < 0) )
    {
        return true;
    } else if ( (row >= height) || (row < 0) )
    {
        return true;
    }else if ( getGrid(row,column) )
    {
        return true;
    }

    else{
        return false;
    }
}


char* GridSystem::initializeGrid(){
    grid = (char*) malloc(sizeof(char)*height*width);
  
    return grid;
}

char GridSystem::getGrid(int y, int x){
    return grid[y*width+x];
}
void GridSystem::setGrid(int y, int x, char value){
    grid[y*width+x] = value;
}