#include "AntColony.hpp"



AntColony::AntColony()
{
}

AntColony::AntColony(int iteration, int evapRate, int amountOfAnts)
{
    this->iteration = iteration;
    this->evapRate = evapRate;
    this->amountOffAnts = amountOfAnts; 
}


AntColony::~AntColony()
{
    delete [] antsArray;
}


vector<int> AntColony::getBestPath(){

    // start condition
    setStartEndPoint();
    createAnts();
    antsReachedGoal = 0;

    for (int i = 0; i < iteration; i++)
    {
        cout<<"\nIteration:" << i<<endl;
        while (antsReachedGoal < amountOffAnts-1)
        {
            calculateNextNode();
        }
        pheromoneUpdate();
        //printPath();

        // Return Ants at the goal back to the start:
        antsReachedGoal = 0;
        if (i < iteration -1)
        {
            for (int a = 0; a < amountOffAnts; a++)
            {
                antsArray[a].path.resize(1);
            }
        }

    }

    //find ant with shortest path
    int minPath = antsArray[0].path.size();
    int antIndex = 0;

    for (int i =1 ; i < amountOffAnts; i++)
    {
        if (antsArray[i].path.size() < minPath)
        {
            minPath = antsArray[i].path.size();
            antIndex = i;
        }
    }


    int a;
    vector<int> bestPath;
    for (int i=0; i<antsArray[antIndex].path.size(); i++)
    {
        a = antsArray[antIndex].path[i].getId();
        bestPath.push_back(a);
    }

    cout << endl;


    return bestPath;

}


void AntColony::setStartEndPoint(){
    int *startArray = theMap.getStartIndex();
    startPoint = Node(startArray[0], startArray[1], theMap.width );     //*(startArray + 1)
    int *endArray = theMap.getEndIndex();
    endPoint = Node(endArray[0], endArray[1], theMap.width );
}


bool AntColony::reachedGoal(Ant currentAnt){

    if (currentAnt.getLastNodeId() == endPoint.getId())
    {
        return true;
    }else{
        return false;
    }

}


void AntColony::createAnts(){

    antsArray = new Ant[amountOffAnts];     //Array of ants
    for (size_t i = 0; i < amountOffAnts; i++)
    {
       antsArray[i] = Ant(startPoint);      //create Ant for each element
       antsArray[i].id = i;
    }
}



bool AntColony::checkCondition(Node* currentNode, Node* prevNode, pair<int, int> steps ){

    int nextId = theMap.width * (currentNode->getRow() + steps.second + 1 -1 )
                     + currentNode->getColumn() + steps.first + 1;  // bin ich mir nicht sicher

    if (prevNode == NULL)
    {
            if ( !theMap.checkIfObstacleBorder( currentNode->getColumn() + steps.first,
                                        currentNode->getRow() + steps.second ) )
            {
                return true;
            }
            else
            {
                return false;
            }
    }else{
        if ( !theMap.checkIfObstacleBorder( currentNode->getColumn() + steps.first,
                                            currentNode->getRow() + steps.second )
                &&  nextId != prevNode->getId() )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void AntColony::calculateNextNode(){
    //room for improvement: dont choose previous Node

    // getLastNode not necessary becouse path is public now
    vector <Node> surroundigNodes;
    double probAddition = 0;

    Node* currentNode = NULL;
    Node* prevNode = NULL;




    //for each Ant
    for (int i = 0; i < amountOffAnts; i++){

        //if the ant has already reached its destination:
        if ( !reachedGoal(antsArray[i]) )
        {
            currentNode = &antsArray[i].path.back();
            if (antsArray[i].path.size() != 1){
                prevNode = &antsArray[i].path[antsArray[i].path.size()-2];
            }

            /*--------create surronding Nodes which are available (no obstacles) and not previous Node---------*/
            // left Node

            if (checkCondition(currentNode, prevNode, make_pair(-1,0)))
            {
                surroundigNodes.push_back( Node( currentNode->getColumn() -1, currentNode->getRow(), theMap.width ) );
                surroundigNodes.back().isDiagonal = 1;
            }

            // left-down Node
            if ( checkCondition(currentNode, prevNode, make_pair(-1,+1)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn() -1, currentNode->getRow() +1, theMap.width ) );
                surroundigNodes.back().isDiagonal = sqrt(2);
            }

            // down Node
            if ( checkCondition(currentNode, prevNode, make_pair(0,+1)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn(), currentNode->getRow() +1, theMap.width ) );
                surroundigNodes.back().isDiagonal = 1;
            }

            // right-down Node
            if ( checkCondition(currentNode, prevNode, make_pair(+1,+1)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn() +1, currentNode->getRow() +1, theMap.width ) );
                surroundigNodes.back().isDiagonal = sqrt(2);
            }

            // right Node
            if ( checkCondition(currentNode, prevNode, make_pair(+1,0)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn() +1, currentNode->getRow(), theMap.width  ) );
                surroundigNodes.back().isDiagonal = 1;
            }

            // right-up Node
            if ( checkCondition(currentNode, prevNode, make_pair(+1,-1)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn() +1, currentNode->getRow() -1, theMap.width ) );
                surroundigNodes.back().isDiagonal = sqrt(2);
            }

            // up Node
            if ( checkCondition(currentNode, prevNode, make_pair(0,-1)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn(), currentNode->getRow() -1, theMap.width ) );
                surroundigNodes.back().isDiagonal = 1;
            }

            // left-up Node
            if ( checkCondition(currentNode, prevNode, make_pair(-1,-1)) )
            {
                surroundigNodes.push_back( Node( currentNode->getColumn() -1, currentNode->getRow() -1, theMap.width ) );
                surroundigNodes.back().isDiagonal = sqrt(2);
            }


            /*----------------------------calculate probability--------------------------------*/
            // calculate for each Node the tempProb
            for (Node& a: surroundigNodes)
            {
                // pointer to Edge beween current node and one of the surronding nodes
                if (a.getId() < antsArray[i].getLastNodeId())
                {
                    res = pheromonEdges.find(make_pair( a.getId() , antsArray[i].getLastNodeId() ) );
                }
                else
                {
                    res = pheromonEdges.find(make_pair( antsArray[i].getLastNodeId(), a.getId() ) );
                }

                if (res != pheromonEdges.end())
                {
                    a.tempProb = abs(pow(res->second, alpha)) + pow((1/a.isDiagonal), beta);
                }
                else
                {
                    a.tempProb = 0;
                }



            }

            // adds the sum under the fraction bar
            probAddition=0; // initialize the summ of propabilities to 0
            for (Node& a: surroundigNodes)
            {
                probAddition += a.tempProb; //+=  nicht =+
            }

            // last step of the probability calculation for each surrounding node
            for (Node& a: surroundigNodes)
            {
                if(probAddition)
                    a.prob = a.tempProb / probAddition; // normalized propability
                else
                    a.prob = 0;
            }

            /*----------------------------find highest probabilities-------------------------------*/
            // cpu intensive section - could be improved in further versions.
            vector<int> position;
            double currentMax = 0;
            int a = 0;
            double psum=0;
            for (double p = 0; p < 1; p+=0.01)
            {
                if(a>surroundigNodes.size())
                    break;
                if (surroundigNodes[a].prob+psum > p)
                {
                    position.push_back(a);
                }
                else
                {
                    psum+=surroundigNodes[a].prob;
                    a++;
                }
            }

            /*---------------------random choose between the highest probabilities--------------------*/
            // rand() % position.size() :   choose randomly the index in position vektor with:
            // position[] :     return int value where the surrondingNodes are listed according to their propability
			
            Node nextNode;
            if (position.size() == 0)       // if all surroundig nodes have the probability of 0
            {
                nextNode = surroundigNodes[ rand() % surroundigNodes.size()] ;
            }
            else
            {
                nextNode = surroundigNodes[ position[rand() % position.size()] ];
                position.clear();
            }
            surroundigNodes.clear();

            /*---------------------------------------insert new Node----------------------------------*/

            antsArray[i].insertNewNode(nextNode);

            if (nextNode.getId() == endPoint.getId())
            {
                antsReachedGoal++;
            }
        }
    }
}


void AntColony::pheromoneUpdate(){

    int first, second;
    map <pair <int, int> , double> iterationEdges;
    map <pair <int, int> , double> antEdges;
    map <pair<int,int>, double>:: iterator res;


    /*
    * for each ant, the pheromone value ( Q1 / pathlength) of the current iteration is
    * calculated and stored in antEdges. This extra map is neccessary if one ant passed one edge twice.
    *  If several ants have passed the same edge, this is added in iterationEdges.
    */

    for (int  a = 0; a < amountOffAnts; a++)
    {
        /*------------------------------------calculate pheromon Values of current ant-----------------*/

        // each edge in path - compare each Node with next node in path
        for (int b = 0; b < (antsArray[a].path.size() -1 ); b++)
        {
            //put the lower id value at the beginning - room for improvement: comp function with hash
            if (antsArray[a].path[b].getId() < antsArray[a].path[b+1].getId())
            {
                first = antsArray[a].path[b].getId();
                second = antsArray[a].path[b+1].getId();
            }else
            {
                first = antsArray[a].path[b+1].getId();
                second = antsArray[a].path[b].getId();
            }

            //insert edge if it doesnt exist already in the antEdge map
            res = antEdges.find(make_pair(first, second));
            if (res == antEdges.end())
            {
                //the edge doesnt exist yet
                antEdges.insert( { {first,second}, (Q / antsArray[a].path.size()) } );
            }
        }
        /*------------------------------------add antEdges in iterationEdges----------------*/

        // insert all antEdges in interationEdges or add if they already exist becouse of other ants in the current iteration
        for (auto& edge: antEdges)
        {
            res = iterationEdges.find(edge.first);
            if ( res == iterationEdges.end() )
            {
                iterationEdges.insert({edge.first, edge.second});
            }
            else
            {
                res->second += edge.second;
            }
        }

        antEdges.clear();

        if (false)
        {
            cout << "Ant: "<< a << endl;
            for(auto &pair : iterationEdges)
            {
                cout << pair.first.first <<", "<< pair.first.second << ":   " << pair.second << endl;
            }
            cout<< endl;
        }



    }


    /*------------------------------------add the iterationEdges to the generell PheromonEdges-----------------*/
    // add iterationEdge in pheromonEdge
    for (auto& i: pheromonEdges)
    {
        res = iterationEdges.find(i.first);
        //if pheromonEdge exist in currentEdges
        if (iterationEdges.find(i.first) != iterationEdges.end())
        {
            //calculate with new value and add pheromon from currentEdges
            i.second = (1-evapRate) * i.second + iterationEdges.find(i.first)->second;
            iterationEdges.erase(res->first);
        }
        else
        {
            i.second = (1-evapRate) * i.second;
        }

    }

    // insert the left over iterationEdges in PheromonEdges
    for (auto& edge : iterationEdges)
    {
        pheromonEdges.insert({edge.first, edge.second});
    }

    iterationEdges.clear();


}

#include <iomanip>
void AntColony::printGrid(){
    setStartEndPoint();
    for (int i = 0; i < theMap.height; ++i)
    {
        //cout << i <<"   ";
        for (int j = 0; j < theMap.width; ++j)
        {
            if ((startPoint.getRow()  == i) && (startPoint.getColumn() == j))
            {
                cout << "  S ";
            }
            else if((endPoint.getRow() == i) && (endPoint.getColumn() == j))
            {
                cout << "  G ";
            }
            else if(theMap.getGrid(i,j)==true){
                cout << "  X ";
            }
            else
            {
                int x = theMap.width * (i + 1 -1 ) + j + 1;
                cout << std::setw(3) << x <<" ";
            }
        }
        std::cout << std::endl;
    }
}


void AntColony::printPath(){
    int average = 0;
    int minimal = antsArray[0].path.size();

    for (int b = 0; b < amountOffAnts; b++)
    {
        //cout << "Ant " << b << ":    "<< antsArray[b].path.size()<< "\n";
        average +=  antsArray[b].path.size();
        
        if(minimal>antsArray[b].path.size())
            minimal = antsArray[b].path.size();
    }
    average = average / amountOffAnts;
    cout<< "average: " << average << endl;
    cout<< "minimal: " <<           minimal          << std::endl;
}
