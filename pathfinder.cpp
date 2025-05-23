#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    int gCost, hCost, fCost;
    Node* parent;

    Node(int x, int y, Node* parent = nullptr)
        : x(x), y(y), gCost(0), hCost(0), fCost(0), parent(parent) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

vector<Node*> getNeighbors(Node* current, const vector<vector<int>>& grid) {
    vector<Node*> neighbors;
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for (auto d : directions) {
        int newX = current->x + d.first;
        int newY = current->y + d.second;

        if (isValid(newX, newY, rows, cols) && grid[newX][newY] == 0) {
            neighbors.push_back(new Node(newX, newY, current));
        }
    }
    return neighbors;
}

bool nodeInList(Node* node, const vector<Node*>& list) {
    for (auto n : list) {
        if (*n == *node) return true;
    }
    return false;
}

Node* findNodeInList(Node* node, vector<Node*>& list) {
    for (auto n : list) {
        if (*n == *node) return n;
    }
    return nullptr;
}

void reconstructPath(Node* endNode, vector<vector<int>>& grid) {
    Node* current = endNode->parent;
    while (current && current->parent) {
        grid[current->x][current->y] = 2;
        current = current->parent;
    }
}

void printGrid(const vector<vector<int>>& grid) {
    for (auto& row : grid) {
        for (auto cell : row) {
            if (cell == 1) cout << "# ";
            else if (cell == 0) cout << ". ";
            else if (cell == 2) cout << "* ";
        }
        cout << endl;
    }
}

void aStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> end) {
    vector<Node*> openList;
    vector<Node*> closedList;

    Node* startNode = new Node(start.first, start.second);
    startNode->gCost = 0;
    startNode->hCost = heuristic(start.first, start.second, end.first, end.second);
    startNode->fCost = startNode->gCost + startNode->hCost;

    openList.push_back(startNode);

    while (!openList.empty()) {
        auto currentIt = min_element(openList.begin(), openList.end(),
            [](Node* a, Node* b) { return a->fCost < b->fCost; });
        Node* currentNode = *currentIt;

        if (currentNode->x == end.first && currentNode->y == end.second) {
            cout << "Path found:\n";
            reconstructPath(currentNode, grid);
            printGrid(grid);
            for (auto n : openList) delete n;
            for (auto n : closedList) delete n;
            return;
        }

        openList.erase(currentIt);
        closedList.push_back(currentNode);

        for (auto neighbor : getNeighbors(currentNode, grid)) {
            if (nodeInList(neighbor, closedList)) {
                delete neighbor;
                continue;
            }

            int tentative_gCost = currentNode->gCost + 1;

            bool inOpen = nodeInList(neighbor, openList);
            Node* openNode = nullptr;
            if (inOpen) {
                openNode = findNodeInList(neighbor, openList);
            }

            if (!inOpen || tentative_gCost < (openNode ? openNode->gCost : INT_MAX)) {
                neighbor->gCost = tentative_gCost;
                neighbor->hCost = heuristic(neighbor->x, neighbor->y, end.first, end.second);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = currentNode;

                if (!inOpen) {
                    openList.push_back(neighbor);
                } else {
                    delete neighbor;
                }
            } else {
                delete neighbor;
            }
        }
    }

    cout << "No path found.\n";
    for (auto n : openList) delete n;
    for (auto n : closedList) delete n;
}

int main() {
    vector<vector<int>> grid = {
        {0,0,0,0,0,1,0,0,0,0},
        {1,1,0,1,0,1,0,1,1,0},
        {0,0,0,1,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,0,1,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    pair<int,int> start = {0, 0};
    pair<int,int> end = {6, 9};

    cout << "Maze grid legend:\n# = Wall\n. = Free path\n* = Path found\n\n";
    aStar(grid, start, end);

    return 0;
}
