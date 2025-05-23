A* Pathfinding Algorithm in C++

This repository contains a C++ implementation of the A* pathfinding algorithm on a 2D grid. The program finds the shortest path from a start point to an end point while navigating around obstacles.

Overview
The A* algorithm is a popular pathfinding and graph traversal technique used extensively in AI and robotics for finding the optimal path between two points. This project demonstrates the algorithm on a grid maze where cells can be free paths or walls.

Features
Grid-based maze navigation with obstacles.

Manhattan distance heuristic for estimating shortest path.

Dynamic open and closed lists to track nodes.

Path reconstruction and visualization on the grid.

Easy-to-understand, modular code structure.

How It Works
The grid is represented as a 2D vector, where 0 is a free path and 1 is a wall.

The algorithm starts at a designated start node and explores neighboring nodes.

Each node maintains:

gCost: Cost from the start node.

hCost: Heuristic cost to the end node (Manhattan distance).

fCost: Sum of gCost and hCost.

The node with the lowest fCost is expanded until the end node is reached.

Once the path is found, it is marked on the grid and displayed.

Grid Legend
# — Wall/Obstacle

. — Free path

* — Path found by A*


Usage
Clone the repository:
git clone https://github.com/your-username/astar-pathfinding-cpp.git

Navigate to the project folder and compile:
g++ -o astar main.cpp
Run the executable:
./astar


## Code Structure

| Component           | Description                                                                                         |
|---------------------|-----------------------------------------------------------------------------------------------------|
| **Node struct**     | Represents a cell in the grid with:                                                                  |
|                     | - Coordinates: `x`, `y`                                                                             |
|                     | - Costs: `gCost` (start to current), `hCost` (heuristic to goal), `fCost` (`gCost + hCost`)         |
|                     | - `parent` pointer to the previous node for path reconstruction                                      |
| **heuristic function** | Calculates Manhattan distance between two points `(x1, y1)` and `(x2, y2)`; estimates cost to goal |
| **isValid function**  | Checks if a coordinate `(x, y)` is inside grid boundaries                                           |
| **getNeighbors function** | Returns all valid neighboring nodes (up, down, left, right) that are walkable                     |
| **aStar function**   | Implements the A* algorithm:                                                                        |
|                     | - Manages open and closed node lists                                                               |
|                     | - Picks node with lowest `fCost` for exploration                                                   |
|                     | - Updates costs and parents for neighbors                                                          |
|                     | - Stops when goal is found or no path exists                                                       |
| **reconstructPath function** | Traces back from end node to start using `parent` pointers and marks the path on the grid    |
| **printGrid function** | Displays the grid with symbols for walls (`#`), free paths (`.`), and found path (`*`)             |
