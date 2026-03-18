#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int BFS(int startX, int startY, int goalX, int goalY, int *distance) {

    Node queue[ROW * COL];
    int front = 0, rear = 0;

    queue[rear++] = (Node){startX, startY};
    visited[startX][startY] = 1;

    int level[ROW][COL] = {0};

    while (front < rear) {

        Node current = queue[front++];

        if (current.x == goalX && current.y == goalY) {
            *distance = level[current.x][current.y];
            return 1;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY)) {
                visited[newX][newY] = 1;
                parentX[newX][newY] = current.x;
                parentY[newX][newY] = current.y;
                level[newX][newY] = level[current.x][current.y] + 1;
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

    srand(time(NULL));

    int startX, startY, goalX, goalY;
    int densityChoice;
    int obstacleCount;
    int shortestDistance;

    printf("Grid Size: %dx%d\n", ROW, COL);

    printf("Enter Start Coordinates (row col): ");
    scanf("%d %d", &startX, &startY);

    printf("Enter Goal Coordinates (row col): ");
    scanf("%d %d", &goalX, &goalY);

    if (startX < 0 || startX >= ROW || startY < 0 || startY >= COL ||
        goalX < 0 || goalX >= ROW || goalY < 0 || goalY >= COL) {
        printf("Invalid coordinates!\n");
        return 0;
    }

    printf("\nSelect Obstacle Density:\n");
    printf("1. Low\n2. Medium\n3. High\n");
    scanf("%d", &densityChoice);

    if (densityChoice == 1)
        obstacleCount = 15;
    else if (densityChoice == 2)
        obstacleCount = 25;
    else
        obstacleCount = 40;

    // Initialize grid
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++) {
            grid[i][j] = 0;
            visited[i][j] = 0;
        }

    // Generate obstacles
    for (int i = 0; i < obstacleCount; i++) {
        int r = rand() % ROW;
        int c = rand() % COL;
        if (!(r == startX && c == startY) &&
            !(r == goalX && c == goalY))
            grid[r][c] = 1;
    }

    if (BFS(startX, startY, goalX, goalY, &shortestDistance)) {
        tracePath(startX, startY, goalX, goalY);
        printf("\nPath Found!\n");
        printf("Shortest Distance: %d\n\n", shortestDistance);
    } else {
        printf("\nNo Path Found!\n");
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
