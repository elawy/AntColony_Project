#include"Node.hpp"


Node::Node(){
    
}

Node::Node(int arrayIndex_c , int arrayIndex_r, int width)
{
    column = arrayIndex_c ;
    row = arrayIndex_r;
    calculateId(width);
}

Node::~Node()
{
}

/**
 * @brief calculate SerialNumber from this Node
 * x = row 
 * y = coloum
 */
void  Node::calculateId(int width){

    this->id = width * (row + 1 -1 ) + column + 1;   
    if (id < 1)
    {
       cout << "someting went wrong" << endl;
    }
    
}

int Node::getId(){
    return id;
}


int Node::getRow(){
    return row;
}

int Node::getColumn(){
    return column;
}