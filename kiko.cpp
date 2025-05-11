#include <iostream>
#include <stack>
#include <queue>
using namespace std;

const int ROWS = 4;
const int COLS = 5;

// maze
char maze[ROWS][COLS] = {
    {'S', '0', '1', '1', '1'},
    {'1', '0', '0', '0', '1'},
    {'1', '1', '1', '0', '0'},
    {'1', '1', '1', '1', 'E'}
};

// dfs and bfs
bool visitedDFS[ROWS][COLS] = {false};
bool visitedBFS[ROWS][COLS] = {false};

// directions 
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct Position {
    int x, y;
};

// function
void printMaze() {
    cout << "Maze : " << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// check validation
bool isValidDFS(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS &&
            (maze[x][y] == '0' || maze[x][y] == 'E') && !visitedDFS[x][y]);
}

bool isValidBFS(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS &&
            (maze[x][y] == '0' || maze[x][y] == 'E') && !visitedBFS[x][y]);
}

// stack
bool dfsMazeSolver(int startX, int startY) {
    stack<Position> s;
    s.push({startX, startY});
    visitedDFS[startX][startY] = true;

    cout << "Using Stack:\n" << endl;

    while (!s.empty()) {
        Position current = s.top();
        s.pop();

        cout << "destination (" << current.x << ", " << current.y << ")" << endl;

        // path
        if (maze[current.x][current.y] == '0') {
            maze[current.x][current.y] = '*';
        }

        if (maze[current.x][current.y] == 'E') {
            cout << "DFS completed" << endl << endl;
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValidDFS(newX, newY)) {
                s.push({newX, newY});
                visitedDFS[newX][newY] = true;
            }
        }
    }

    cout << "DFS no path" << endl << endl;
    return false;
}

// queue
bool bfsMazeSolver(int startX, int startY) {
    queue<Position> q;
    q.push({startX, startY});
    visitedBFS[startX][startY] = true;

    cout << "Using Queue:" << endl << endl;

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        cout << "destination (" << current.x << ", " << current.y << ")" << endl;

        //path
        if (maze[current.x][current.y] == '0') {
            maze[current.x][current.y] = '*';
        }

        if (maze[current.x][current.y] == 'E') {
            cout << "BFS completed\n" << endl;
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValidBFS(newX, newY)) {
                q.push({newX, newY});
                visitedBFS[newX][newY] = true;
            }
        }
    }

    cout << "BFS no path" << endl << endl;
    return false;
}

int main() {
    int startX = 0, startY = 0;

    printMaze();

    dfsMazeSolver(startX, startY);
    bfsMazeSolver(startX, startY);

    cout << "Path Marked '*' : " << endl << endl;
    printMaze();

    return 0;
}
