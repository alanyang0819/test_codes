#include<iostream>
using namespace std;

const int dim1= 100, dim2 = 100; 
void readMaze(char maze[dim1][dim2], int row, int column, int &startX, int &startY)
{
  for(int i = 0; i < row; i++){
    for(int k = 0; k < column; k++){
      if(maze[i][k] == 'S'){
        startX = i;
        startY = k;
      }
    }
  }
}

enum direction_of_move {move_left, move_up, move_right, move_down};

void move(direction_of_move &direction, char maze[][dim2], int row, int column, int &currX, int &currY, int &numOfMove)
{
    switch (direction)
    {
    case move_left:
        if((currY-1 >= 0) && maze[currX][currY-1] != '1')
        {
            direction = move_left;
            currY--;
        }
        else if((currX + 1 < row) && maze[currX + 1][currY] != '1')
        {
            direction = move_up;
            currX++;
        }
        else if((currX - 1 >= 0) && maze[currX - 1][currY] != '1')
        {
            direction = move_down;
            currX--;
        }
        
        
        else if((currY+1 < column) && maze[currX][currY+1] != '1')
        {
            direction = move_right;
            currY++;
        }
        
        numOfMove++;
        break;
    case move_up:
        if((currY-1 >= 0) && maze[currX][currY-1] != '1')
        {
            direction = move_left;
            currY--;
        }
        else if((currX + 1 < row) && maze[currX + 1][currY] != '1')
        {
            direction = move_up;
            currX++;
        }
        
        else if((currY+1 < column) && maze[currX][currY+1] != '1')
        {
            direction = move_right;
            currY++;
        }
        
        else if((currX - 1 >= 0) && maze[currX - 1][currY] != '1')
        {
            direction = move_down;
            currX--;
        }
        
        
        numOfMove++;
        break;
    case move_right:
        if((currX + 1 < row) && maze[currX + 1][currY] != '1')
        {
            direction = move_up;
            currX++;
        }
        else if((currY+1 < column) && maze[currX][currY+1] != '1')
        {
            direction = move_right;
            currY++;
        }
        else if((currX - 1 >= 0) && maze[currX - 1][currY] != '1')
        {
            direction = move_down;
            currX--;
        }
        
        
        else if((currY-1 >= 0) && maze[currX][currY-1] != '1')
        {
            direction = move_left;
            currY--;
        }
        
        
        numOfMove++;
        break;
    case move_down:
        if((currY-1 >= 0) && maze[currX][currY-1] != '1')
        {
            direction = move_left;
            currY--;
        }
        else if((currY+1 < column) && maze[currX][currY+1] != '1')
        {
            direction = move_right;
            currY++;
        }
        else if((currX - 1 >= 0) && maze[currX - 1][currY] != '1')
        {
            direction = move_down;
            currX--;
        }
        
        
        
        else if((currX + 1 < row) && maze[currX + 1][currY] != '1')
        {
            direction = move_up;
            currX++;
        }
        numOfMove++;
        break;
    default:
        break;
    }
}

int findPath(char maze[dim1][dim2], int row, int column, int &startX, int &startY, int &targetX, int &targetY)
{
  
  direction_of_move direction = move_left;
  int numOfMove = 0, currX = startX, currY = startY;
  
    do
    {
        move(direction, maze, row, column, currX, currY, numOfMove);
    }
    while(maze[currX][currY] == '0');
    targetX = currX;
    targetY = currY;

    return numOfMove;

  
}

int main()
{
  int numTest;
  char maze[dim1][dim2];
  cin >> numTest;
  for(int j = 0; j < numTest; j++){
    int column;
    int row;
    int numOfMove;
    int startX;
    int startY;
    int targetX;
    int targetY;
    cin >> row >> column;
    for(int x = 0; x < row; x++){
      for(int y = 0; y < column; y++){
        cin >> maze[x][y];
      }
    }
    readMaze(maze, row, column, startX, startY);
    numOfMove = findPath(maze, row, column, startX, startY, targetX, targetY);

    cout << "# Source coordinates: (" << startX + 1 << "," << startY + 1 << "). Target coordinates: (" 
    << targetX + 1 << "," << targetY + 1 << "), Distance traveled: " << numOfMove << endl;
  }
  return 0;
}
