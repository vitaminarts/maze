#include <iostream>
#include <windows.h>
using namespace std;

//Maze size
const int N = 9;

struct stack
{
    int n;
    int top = 0;
    int* row;
    int* col;
    stack(int length)
    {
        n = length;
        row = new int[length * length];
        col = new int[length * length];
    }

    void push(int i, int j)
    {
        row[top] = i;
        col[top] = j;
        top++;
    }

    int** pop()
    {
        int** pop = new int* [1];
        pop[0] = new int[2];
        if (top > 0)
        {
            pop[0] = new int[2];
            pop[0][0] = row[top - 1];
            pop[0][1] = col[top - 1];
            top--;
        }
        return pop;
    }

};

//Show maze
void show(int maze[N][N]);
//Check Next position
bool checkRight(int maze[N][N], int i, int j);
bool checkLeft(int maze[N][N], int i, int j);
bool checkTop(int maze[N][N], int i, int j);
bool checkBottom(int maze[N][N], int i, int j);
//Move to the next position
bool goRight(int maze[N][N], int i, int j, stack& s_tack);
bool goLeft(int maze[N][N], int i, int j, stack& s_tack);
bool goTop(int maze[N][N], int i, int j, stack& s_tack);
bool goBottom(int maze[N][N], int i, int j, stack& s_tack);
//Solve
void Move(int maze[N][N], int x, int y, int direction, stack &st_ack);
//Check if maze solved
bool isEnd(int i, int j);

int main()
{ 
    stack* s = new stack(N);
    int x = 0, y = 0;

    int maze[N][N];
    // Fill the maze with 0s and 1s
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maze[i][j] = rand() % 2;
        }
    }
    int row = 0, col = 0;
    while (row != N - 1 || col != N - 1) {
        maze[row][col] = 0;
        if (row == N - 1) {
            col++;
        }
        else if (col == N - 1) {
            row++;
        }
        else if (rand() % 2 == 0) {
            row++;
        }
        else {
            col++;
        }
    }
    maze[row][col] = 0;

    show(maze);
    Move(maze, x,y,0,*s);

	return 0;
}

//////////////////////////////////////////////////
void show(int maze[N][N])
{
    cout << "|||  The Maze  |||" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (maze[i][j] == 10)
                cout << (char)254 << " ";
            else if(maze[i][j] == 9)
                cout << "0 ";
            else
                cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}
//////////////////////////////////////////////////
bool checkRight(int maze[N][N], int i , int j)
{
    if (j < N - 1 && maze[i][j + 1] == 0)   
        return true;
    return 0;
}
bool checkLeft(int maze[N][N], int i, int j)
{
    if ( j > 0 && maze[i][j - 1] == 0)
        return true;
    return 0;
}
bool checkTop(int maze[N][N], int i, int j)
{
    if (i > 0 && maze[i - 1][j] == 0)
        return true;
    return 0;
}
bool checkBottom(int maze[N][N], int i, int j)
{
    if (i < N-1 && maze[i+1][j] == 0)
        return true;
    return 0;
}
//////////////////////////////////////////////////
bool goRight(int maze[N][N], int i, int j,stack &s_tack)
{
    if (checkRight(maze,i,j))
    {
        s_tack.push(i, j+1);
        return true;
    }
    return false;
}
bool goLeft(int maze[N][N], int i, int j, stack& s_tack)
{
    if (checkLeft(maze, i, j))
    {
        s_tack.push(i, j-1);
        return true;
    }
    return false;
}
bool goTop(int maze[N][N], int i, int j, stack& s_tack)
{
    if (checkTop(maze, i, j))
    {
        s_tack.push(i-1, j);
        return true;
    }
    return false;
}
bool goBottom(int maze[N][N], int i, int j, stack& s_tack)
{
    if (checkBottom(maze, i, j))
    {
        s_tack.push(i + 1, j);
        return true;
    }
    return false;
}
//////////////////////////////////////////////////
void Move(int maze[N][N], int x, int y, int direction, stack &st_ack) // direction : 0 Right 1 Bottom 2 Top 3 Left
{
    system("cls");
    if (!isEnd(x, y))
    {
        show(maze);
        Sleep(300);
        if (direction == 0)
        {
            if (goRight(maze, x, y, st_ack))
            {
                maze[x][y] = 10;
                y++;
                Move(maze, x, y, 0, st_ack);
            }
            else
            {
                Move(maze, x, y, 1, st_ack);
            }
        }
        else if (direction == 1)
        {
            if (goBottom(maze, x, y, st_ack))
            {
                maze[x][y] = 10;
                x++;
                Move(maze, x, y, 0, st_ack);
            }
            else
            {
                Move(maze, x, y, 2, st_ack);
            }
        }
        else if (direction == 2)
        {
            if (goTop(maze, x, y, st_ack))
            {
                maze[x][y] = 10;
                x--;
                Move(maze, x, y, 0, st_ack);
            }
            else
            {
                Move(maze, x, y, 3, st_ack);
            }
        }
        else if (direction == 3)
        {
            if (goLeft(maze, x, y, st_ack))
            {
                maze[x][y] = 10;
                y--;
                Move(maze, x, y, 0, st_ack);
            }
            else
            {
                int** pre = st_ack.pop();
                maze[pre[0][0]][pre[0][1]] = 9;
                x = pre[0][0];
                y = pre[0][1];
                Move(maze, x, y, 0, st_ack);
            }
        }
    }
    else
    {
        maze[N - 1][N - 1] = 10;
        show(maze);
    }
}
//////////////////////////////////////////////////
bool isEnd(int i, int j)
{
    if (i == N - 1 && j == N - 1)
        return true;
    return false;
}
//////////////////////////////////////////////////
