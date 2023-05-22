# include "Ant.hpp"

Ant::Ant(){

}

/**
 * @brief Construct a new Ant:: Ant object
 * put the first Node in the List ()
 * give every Ant the same StartPoint
 *
 * @param startPoint
 */

Ant::Ant(Node startPoint)
{
    path.push_back(startPoint);
}

Ant::~Ant()
{
}

int Ant::getLastNodeId(){
    return path.back().getId();
}

int* Ant::getLastNodeIndex(int* index){
    index[0] = path.back().getColumn();
    index[1] = path.back().getRow(); 

    return index;
}

int* Ant::getPenultimate(int* index){
    index[0] = path[path.size()-1].getColumn();
    index[1] = path[path.size()-1].getRow(); 

    return index;
}


void Ant::insertNewNode(Node newOne){
    path.push_back(newOne);
}