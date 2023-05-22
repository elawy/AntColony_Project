
# ifndef _AntColony_h_
# define _AntColony_h_


# include "Ant.hpp"
# include "GridSystem.hpp"

using namespace std;

#include <vector>
#include <utility>
#include <math.h>
#include <map>


class AntColony
{
private:

    //Parameter
    int amountOffAnts = 10;
    int antsReachedGoal;

    int iteration = 10;

    double  alpha = 1;
    double beta = 0.2;
    double Q = 10;
    double evapRate = 0.5;

    Ant* antsArray = NULL;      //ptr_antsArray

    Node startPoint;
    Node endPoint;

    map <pair <int, int> ,double> pheromonEdges;
    map <pair<int,int>, double>:: iterator res;

    void setStartEndPoint();
    void createAnts();
    bool reachedGoal(Ant currentAnt);

    void calculateNextNode();
    void pheromoneUpdate();
    bool checkCondition(Node* currentNode, Node* prevNode, pair<int, int> steps);

    void printPath();


public:

    AntColony();
    AntColony(int iteration, int evapRate, int amountOfAnts);
    ~AntColony();
    void printGrid();
    vector<int> getBestPath();
    void setStart(int x, int y);
    void setEnd(int x, int y);

    GridSystem theMap;
};

#endif

