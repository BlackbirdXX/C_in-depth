#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define MAX_X 15
#define MAX_Y 15
#define MIN_X 0
#define MIN_Y 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

typedef struct tail_t
{
    int x;
    int y;
} tail_t;

typedef struct snake_t
{
    int x;
    int y;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

struct snake_t initSnake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; ++i)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

void printSnake(struct snake_t snake)
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            matrix[i][j] = ' ';
        }
    }

    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; ++i)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    }
    for (int j = 0; j < MAX_Y; ++j)
    {
        for (int i = 0; i < MAX_X; ++i)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

snake_t moveLeft(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x = snake.x - 1;
    if (snake.x < MIN_X)
    {
        snake.x = MAX_X - 1;
    }
    return snake;
}

snake_t moveRight(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x = snake.x + 1;
    if (snake.x > MAX_X)
    {
        snake.x = MIN_X + 1;
    }
    return snake;
}

snake_t moveUp(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.y = snake.y - 1;
    if (snake.y < MIN_Y)
    {
        snake.y = MAX_Y - 1;
    }
    return snake;
}

snake_t moveDown(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.y = snake.y + 1;
    if (snake.y > MAX_Y)
    {
        snake.y = MIN_Y + 1;
    }
    return snake;
}
// Проверка движения в нужном направлении
int checkDirection(snake_t snake, int key)
{
    if (key == LEFT)
    {
        if (snake.x - 1 == snake.tail[0].x)
        {
            return 0;
        }
    }
    if (key == UP)
    {
        if (snake.y - 1 == snake.tail[0].y)
        {
            return 0;
        }
    }
    if (key == RIGHT)
    {
        if (snake.x + 1 == snake.tail[0].x)
        {
            return 0;
        }
    }
    if (key == DOWN)
    {
        if (snake.y + 1 == snake.tail[0].y)
        {
            return 0;
        }
    }
    return 1;
}

// Движение змейки
snake_t moveSnake(snake_t snake, int key)
{
    if (key == LEFT)
    {
        snake = moveLeft(snake);
        return snake;
    }
    else if (key == UP)
    {
        snake = moveUp(snake);
        return snake;
    }
    else if (key == RIGHT)
    {
        snake = moveRight(snake);
        return snake;
    }
    else if (key == DOWN)
    {
        snake = moveDown(snake);
        return snake;
    }
    else
        return snake;
}

// Обработка нажатия клавиши
int keyProcessing(snake_t snake, int key)
{
    char ch = getch();
    if (ch == 'w' || ch == 'W')
    {
        if (checkDirection(snake, UP))
        {
            return UP;
        }
        else
            return key;
    }
    if (ch == 's' || ch == 'S')
    {
        if (checkDirection(snake, DOWN))
        {
            return DOWN;
        }
        else
            return key;
    }
    if (ch == 'a' || ch == 'A')
    {
        if (checkDirection(snake, LEFT))
        {
            return LEFT;
        }
        else
            return key;
    }
    if (ch == 'd' || ch == 'D')
    {
        if (checkDirection(snake, RIGHT))
        {
            return RIGHT;
        }
        else
            return key;
    }
    if (ch == 'q' || ch == 'Q')
    {
        exit(0);
    }
}
// Конец игры, если змейка укусила сама себя.
void selfEating(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        if (snake.x == snake.tail[i].x && snake.y == snake.tail[i].y)
        {
            system("cls");
            for (int i = 0; i < MAX_X; ++i)
            {
               if(i == 7){
                    printf("   GAME OVER   \n");
               }
               printf("               \n");
            }
            sleep(3);
            exit(0);
        }
    }
}

int main()
{
    struct snake_t snake = initSnake(10, 5, 4);
    printSnake(snake);
    int key = LEFT;
    while (1)
    {
        snake = moveSnake(snake, key);
        selfEating(snake);
        sleep(1);
        system("cls");
        printSnake(snake);
        if (kbhit())
        {
            key = keyProcessing(snake, key);
        }
    }

    return 0;
}