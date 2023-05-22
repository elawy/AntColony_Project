# AntColony_Project

API used in the main.cpp

![grafik](https://github.com/elawy/AntColony_Project/assets/48498386/54f7f3dc-0ca4-4eb5-ad0e-47b1fda63209)

First an instance of the class AntColony will be initialized. With the parameterized constructor, the 
number of iterations, the evaporation rate and the amount of ants can be chosen. If an individual 
parameter setting is not desired, the default constructor will be used.
Because the map size is depending on the simulation that is used, the variables in the object theMap
must be exchangeable. The dimensions are passed on to the object theMap. Afterwards, the grid, with 
which the ant colony is working, can be initialized dynamically.
Also, the start and end coordinates are saved in theMap object. Important to know is that the row and 
column values represent the indices of an array.
