# AntColony_Project
Path planning is an essential tool of mobile robotic systems in order to achieve short and collision free paths towards a destination. Many of the solutions for more complex maps and obstacles are based on bionic algorithms like the ant colony algorithm.
The goal is to find the best path. Therefore, a finite state of nodes is declared. An artificial ant is a sequence out of these nodes. To find the optimal sequence, mainly two formulas are used, which are explained in the following section.The construction phase and the pheromone state are the basics of the ant system.

## API 
used in the main.cpp

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/e389c730-3fd5-4f0f-a2e2-e3a3814e50e3" width="380" height="200">

First an instance of the class AntColony will be initialized. With the parameterized constructor, the 
number of iterations, the evaporation rate and the amount of ants can be chosen. If an individual 
parameter setting is not desired, the default constructor will be used.
Because the map size is depending on the simulation that is used, the variables in the object theMap
must be exchangeable. The dimensions are passed on to the object theMap. Afterwards, the grid, with 
which the ant colony is working, can be initialized dynamically.
Also, the start and end coordinates are saved in theMap object. Important to know is that the row and 
column values represent the indices of an array.
For a better overview of the map in the test version, it was displayed as a 2-dimensional array. The x
represents obstacles , S the starting point and G the goal.

## Flow Chart

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/311983c5-4d02-4e68-aa5a-8a14191478f4" width="380" height="500">

Each ant chooses the next node. After node selection, there is a 
verification if all ants are at the goal. The ants repeatedly choose the next node in their vicinity until 
every ant has reached the destination. Subsequently the pheromone values are updated. If the iteration value is not reached the ants are set back to the starting point and once more 
commence to find a way to the goal, with the help of the updated pheromone values. When the iteration 
value is reached, the shortest path is chosen from the last iteration.

## Classes

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/c107499a-d6f1-479a-b3f1-c88f5dabf4f9" width="720" height="500">

### AntColony
Basically, the AntColony class is the main actuator. The instance of this class is created in the main or 
in the ROS file and is the only one that will exist. The corresponding API of the algorithm is the public 
functions of the AntColony class. It contains all the functions that calculate the path, as well 
as all the parameters required for that.
It has exactly one instance, named theMap, of the GridSystem class, since access to the map 
information is required for the route calculation. The pointer antsArray allows the accesses to the ants, 
which were created dynamically in the function createAnts(). Just the start end end point of the Type 
Node are, for comparison reasons, saved in AntColony.
### GridSystem
The necessary data is transferred from the visualization program to the instance theMap. Obstacles and 
free fields are stored in the dynamically created array grid*. In this way, the algorithm can check during 
the calculation whether or not there is an obstacle on one of the surrounding fields.
### Ant
The Ant Class has only one important variable. This is the vector path of the type Node. Each ant has
its own path, which begins at the starting point in every iteration. Therefore, in each element of the 
path vector an instance of the class Node is saved. The only purpose of the functions is to make the 
code clearer when calculating the next node in calculateNextNode() whithin AntColony. They ensure 
that small arithmetic tasks, such as calling up the penultimate node id, can be swapped out. This return 
value is used later to prevent the ant from always running for and back or rather not returning to the 
node from which it just came when choosing the next node.
### Node
Each node saves the coordinates and the id. The coordinates x and y, which represent the column and 
row of the pointer grid[][]. The id will be calculated when an instance of Node is created. The id is 
important to save and compare the nodes easily.
id = columnmax * (rowi -1) + columni
The variables tempProb and prob are used to calculate the pheromone value between the current Node 
of the position of the ant and the one of the possible next nodes. With these values, all the possible 
nodes can be compared.


## Math
### calculate probability for next Node

In the code section calculate probability, the formula below is calculated. To accomplish this, the 
individual summations and multiplications will be considered in detail

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/f2720f8d-70a1-479c-8cf4-1fb47bf09705" width="400" height="300">

First, the part below the fraction line is considered. It represents the sum of the probabilities for every 
single reachable node s and is represented in the code with the variable tempProb. Afterwards the 
summation probAddition takes place. In the last step the actual probability prob will be calculated with 
help of a for loop.
To calculate the probability the pheromone values 𝜏𝑖,𝑗 between the current i and the potentially next 
nodes j are retrieved. The distance between the nodes 𝑑𝑖,𝑗 are also saved in the class Node as 
isDiagonal. Only the number 1 or √2 can be stored in the variable.

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/12b57bb2-352b-4f53-85bd-9685f5481c53" width="500" height="200">


### pheromone Update
The calculation of the actual pheromone value is divided into three steps. For this, the temporary maps 
antEdges and iterationEdges are created locally. In the first step, the value left by one ant is calculated. 
This value ∆𝜏 is stored in antEdges. This extra map is necessary in the case that one ant passed one 
edge twice in one iteration. In this occasion it shouldn't save the pheromone value twice. If several 
ants have passed the same edge, this is added in iterationEdges. In the last step, again the existing 
edges must be calculated, even if no ant passed the edge at the current iteration. This is important to 
reduce the pheromone value with the help of the evaporation rate. 

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/db3e4518-0210-43cb-8ad8-1bdeea2a923a" width="530" height="180">

The three steps are implemented in the pseudocode of the algorithm below.

<img src= "https://github.com/elawy/AntColony_Project/assets/48498386/91de5e85-ba7b-4b21-a657-3437e892e9dd" width="450" height="350">




