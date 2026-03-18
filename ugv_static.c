#include <stdio.h>
#include <stdlib.h>

#define ROW 10
#define COL 10

int grid[ROW][COL];
int visited[ROW][COL];
int parentX[ROW][COL];
int parentY[ROW][COL];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Node;

int isValid(int x, int y) {
    return (x >= 0 && x < ROW &&
            y >= 0 && y < COL &&
            grid[x][y] == 0 &&
            visited[x][y] == 0);
}

int BFS(int startX, int startY, int goalX, int goalY) {

    Node queue[ROW * COL];
    int front = 0, rear = 0;

    queue[rear++] = (Node){startX, startY};
    visited[startX][startY] = 1;

    while (front < rear) {

        Node current = queue[front++];

        if (current.x == goalX && current.y == goalY)
            return 1;

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY)) {
                visited[newX][newY] = 1;
                parentX[newX][newY] = current.x;
                parentY[newX][newY] = current.y;
                queue[rear++] = (Node){newX, newY};
            }
        }
    }

    return 0;
}

void tracePath(int startX, int startY, int goalX, int goalY) {

    int x = goalX;
    int y = goalY;

    while (!(x == startX && y == startY)) {
        int tempX = parentX[x][y];
        int tempY = parentY[x][y];

        if (!(x == goalX && y == goalY))
            grid[x][y] = 2;

        x = tempX;
        y = tempY;
    }
}

int main() {

    int startX = 0, startY = 0;
    int goalX = 9, goalY = 9;

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++) {
            grid[i][j] = 0;
            visited[i][j] = 0;
        }

    // Generate random obstacles
    for (int i = 0; i < 25; i++) {
        int r = rand() % ROW;
        int c = rand() % COL;
        grid[r][c] = 1;
    }

    grid[startX][startY] = 0;
    grid[goalX][goalY] = 0;

    if (BFS(startX, startY, goalX, goalY)) {
        tracePath(startX, startY, goalX, goalY);
        printf("Path Found!\n\n");
    } else {
        printf("No Path Found!\n");
        return 0;
    }

    printf("Grid Representation:\n");
    printf("S = Start, G = Goal, 1 = Obstacle, * = Path\n\n");

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {

            if (i == startX && j == startY)
                printf("S ");
            else if (i == goalX && j == goalY)
                printf("G ");
            else if (grid[i][j] == 1)
                printf("1 ");
            else if (grid[i][j] == 2)
                printf("* ");
            else
                printf("0 ");
        }
        printf("\n");
    }

    return 0;
}
