#include <iostream>
#include <vector>
using namespace std;

const int dim1 = 100, dim2 = 100;

// Function to check if a given position is valid in the maze
bool isValid(int x, int y, int row, int column) {
    return x >= 0 && x < row && y >= 0 && y < column;
}

// Function to read the maze and find the starting coordinates
void readMaze(char maze[dim1][dim2], int row, int column, int &startX, int &startY) {
    for (int i = 0; i < row; i++) {
        for (int k = 0; k < column; k++) {
            if (maze[i][k] == 'S') {
                startX = i;
                startY = k;
            }
        }
    }
}

// Function to find the path using the given algorithm
int findPath(char maze[dim1][dim2], int row, int column, int &startX, int &startY, int &targetX, int &targetY, vector<pair<int, int>> &path) {
    // Define directions: 0 - up, 1 - right, 2 - down, 3 - left
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    int currentX = startX;
    int currentY = startY;
    int numOfMove = 0;

    while (true) {
        // Store the path coordinates
        path.push_back({currentX, currentY});

        // Check if the target is reached
        if (maze[currentX][currentY] == 'T') {
            targetX = currentX;
            targetY = currentY;
            cout << "Path found:" << endl;
            return numOfMove;
        }

        // Try moving in the current direction
        int nextX = currentX + dx[numOfMove % 4];
        int nextY = currentY + dy[numOfMove % 4];

        // Check if the next position is valid
        if (isValid(nextX, nextY, row, column) && maze[nextX][nextY] != '1') {
            // Move to the next position
            currentX = nextX;
            currentY = nextY;
            numOfMove++;
        } else {
            // If the next position is not valid, try the next direction
            numOfMove++;
        }

        // Check if we returned to the source without finding the target
        if (currentX == startX && currentY == startY && numOfMove > 4) {
            cout << "No path found." << endl;
            return -1;
        }
    }

    // This point is not reachable in this example
    return -1;
}

int main() {
    int numTest;
    char maze[dim1][dim2];
    cin >> numTest;

    for (int j = 0; j < numTest; j++) {
        int column;
        int row;
        int numOfMove;
        int startX;
        int startY;
        int targetX;
        int targetY;

        cin >> row >> column;

        for (int x = 0; x < row; x++) {
            for (int y = 0; y < column; y++) {
                cin >> maze[x][y];
            }
        }

        readMaze(maze, row, column, startX, startY);

        vector<pair<int, int>> path;  // To store the path coordinates
        numOfMove = findPath(maze, row, column, startX, startY, targetX, targetY, path);

        // Print the path coordinates if a path is found
        if (numOfMove != -1) {
            cout << "Path Coordinates:" << endl;
            for (auto p : path) {
                cout << "(" << p.first + 1 << "," << p.second + 1 << ") ";
            }
            cout << endl;
        }

        cout << "# Source coordinates: (" << startX + 1 << "," << startY + 1 << "). Target coordinates: ("
             << targetX + 1 << "," << targetY + 1 << "), Distance traveled: " << numOfMove << endl;
    }

    return 0;
}

