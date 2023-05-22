#include <iostream>
#include <iomanip>
#include "AntColony.hpp"

char S = 'S';       // Start
char G = 'G';       // Goal
char x =  1 ;       // obstacles

// ROS-Independent main-file to test the algorithm standalone:

// Test map:

char costmap[20][8] = {
        {0,0,0,0,0,0,0,S},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,x,0,0,0,0,0},
        {0,0,x,0,0,0,0,0},
        {0,0,x,x,0,0,0,0},
        {0,0,0,x,0,0,0,0},
        {0,0,0,x,0,0,0,0},
        {0,0,0,x,x,0,0,0},
        {0,0,0,0,x,x,0,0},
        {0,0,0,0,0,x,0,0},
        {0,0,0,0,0,x,0,0},
        {0,0,G,0,0,x,0,0},
        {0,0,0,0,0,x,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
};


int main(int argc, char const *argv[])
{
    srand(time(0)); // set seed for rand() - gives aceptable randomness with little CPU-load
    
    vector<int> path;

    //theColony(interation, evapRate, amountOffAnts)
    AntColony theColony(10, 0.8, 20);      

    // initialize internal gridmap and AntColony class
    theColony.theMap.setDimesions( sizeof(costmap) / sizeof(char*), sizeof(costmap[0]) / sizeof(char) );
    theColony.theMap.initializeGrid();
    
    //copy values & set start & goal
    for(int x=0; x<theColony.theMap.width;  x++)
    for(int y=0; y<theColony.theMap.height; y++){
        if(costmap[y][x]==S){
            costmap[y][x]=0;
            theColony.theMap.setStart(y,x);
        }
        else if(costmap[y][x]==G){
            costmap[y][x]=0;
            theColony.theMap.setEnd(y,x);
        }
        theColony.theMap.setGrid(y,x,costmap[y][x]);
    }
    
    // print map:
    std::cout << "map: \n";
    theColony.printGrid();
    
    // calculate best path
    path = theColony.getBestPath();
    
    // print result:
    std::cout << "best path (l=" << path.size() << "): \n";
    for( auto& a : path){
        std::cout << a << " ";
    }

    std::cout << "\nend" << std::endl;

    return 0;
}
