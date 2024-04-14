#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <Windows.h>

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
    char x;
    char y;
} tail_t;

typedef struct snake_t
{
    char x;
    char y;
    char direction;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

typedef struct eat
{
    char x;
    char y;
    char eatenFood;
} eat;

int getRand()
{
    return rand() % MAX_X;
}

// Создание первой порции еды
struct eat initEat()
{
    srand(time(NULL));
    struct eat eat;
    eat.x = getRand();
    eat.y = getRand();
    eat.eatenFood = 0;
    return eat;
}
// Перекладывание еды на новое место. С учетом свободного места на карте.
eat transferEat(eat eat, snake_t snake, char matrix[MAX_X][MAX_Y])
{
    if ((snake.x == eat.x) && (snake.y == eat.y))
    {
        while (matrix[eat.x][eat.y] != ' ')
        {
            eat.x = getRand();
            eat.y = getRand();
        }
        eat.eatenFood += 1;
    }

    return eat;
}

// Создание змейки
struct snake_t initSnake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.direction = LEFT;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; ++i)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}
// Функция заполнения матрицы
void fillMatrix(char matrix[MAX_X][MAX_Y], struct snake_t *snake, eat eat)
{
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            if (i == 0 || i == MAX_Y - 1)
            {
                matrix[j][i] = '-';
            }
            else if (j == 0 || j == MAX_X - 1)
            {
                matrix[j][i] = '|';
            }
            else
            {
                matrix[j][i] = ' ';
            }
        }
    }
    matrix[snake->x][snake->y] = '@';
    for (int i = 0; i < snake->tsize; i++)
    {
        matrix[snake->tail[i].x][snake->tail[i].y] = '*';
    }
    matrix[eat.x][eat.y] = 'o';
}

// Функция печати заполненой матрицы
void printMatrix(char matrix[MAX_X][MAX_Y], eat eat)
{
    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция роста змейки при условии попадания на точку с едой.
void grownSnake(struct snake_t *head, eat eat)
{
    if ((head->x == eat.x) && (head->y == eat.y))
    {
        if (head == NULL || head->tsize > 100)
        {
            return;
        }
        head->tsize++;
        head->tail[head->tsize - 1].x = head->tail[head->tsize - 2].x;
        head->tail[head->tsize - 1].y = head->tail[head->tsize - 2].y;
    }
}

// Проверка движения в нужном направлении
int checkDirection(snake_t snake, int key)
{
    if (key == LEFT)
    {
        if (snake.direction == RIGHT)
        {
            return 0;
        }
    }
    if (key == UP)
    {
        if (snake.direction == DOWN)
        {
            return 0;
        }
    }
    if (key == RIGHT)
    {
        if (snake.direction == LEFT)
        {
            return 0;
        }
    }
    if (key == DOWN)
    {
        if (snake.direction == UP)
        {
            return 0;
        }
    }
    return 1;
}

// Движение змейки
snake_t moveSnake(snake_t snake, int key)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    if (key == LEFT)
    {
        snake.x = snake.x - 1;
        if (snake.x < MIN_X)
        {
            snake.x = MAX_X - 1;
        }
        snake.direction = LEFT;
    }
    else if (key == UP)
    {
        snake.y = snake.y - 1;
        if (snake.y < MIN_Y)
        {
            snake.y = MAX_Y - 1;
        }
        snake.direction = UP;
    }
    else if (key == RIGHT)
    {
        snake.x = snake.x + 1;
        if (snake.x > MAX_X - 1)
        {
            snake.x = MIN_X;
        }
        snake.direction = RIGHT;
    }
    else if (key == DOWN)
    {
        snake.y = snake.y + 1;
        if (snake.y > MAX_Y - 1)
        {
            snake.y = MIN_Y;
        }
        snake.direction = DOWN;
    }
    return snake;
}

// Функция паузы.
void userPause()
{
    system("cls");
    for (int i = 0; i < MAX_X - 1; ++i)
    {
        if (i == 7)
        {
            printf("             PAUSE          \n");
        }
        printf("               \n");
    }
    printf("To return to the game, press <p>\n");
    char pch;
    while (1)
    {
        if ((pch = getch()) == 'p')
        {
            break;
        }
    }
}

// Обработка нажатия клавиши
int keyProcessing(snake_t snake, int key, eat eat)
{
    char ch = getch();
    fflush(stdin);
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
    if (ch == 'p' || ch == 'P')
    {
        userPause();
        return snake.direction;
    }
    if (ch == 'q' || ch == 'Q')
    {
        system("cls");
        for (int i = 0; i < MAX_X; ++i)
        {
            if (i == 7)
            {
                printf("          END GAME           \n");
                printf("___________Result____________\n");
                printf("Level : %d    Snake : %d meters\n", eat.eatenFood, snake.tsize);
            }
            printf(" \n");
        }
        free(snake.tail);
        sleep(4);
        exit(0);
    }
}

// Конец игры, если змейка укусила сама себя.
void selfEating(snake_t snake, eat eat)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        if (snake.x == snake.tail[i].x && snake.y == snake.tail[i].y)
        {
            system("cls");
            for (int i = 0; i < MAX_X; ++i)
            {
                if (i == 7)
                {
                    printf("         GAME OVER           \n");
                    printf("___________Result____________\n");
                    printf("Level : %d  Snake : %d meters\n", eat.eatenFood, snake.tsize);
                }
                printf("               \n");
            }
            free(snake.tail);
            sleep(3);
            exit(0);
        }
    }
}

// функция печати информации
void printLevel(struct eat eat)
{
    if (eat.eatenFood <= 19)
    {
        printf("Level : %d    Speed : %d%% \n", eat.eatenFood, 5 + 5 * eat.eatenFood);
    }
    else
    {
        printf("Level : %d    Max Speed\n", eat.eatenFood);
    }
    printf("Control : <w> <a> <s> <d>\n");
    printf("Pause : <p>    Exit : <q>\n");
}

// Функция увеличения скорости
int speedBoost(struct eat eat)
{
    if (eat.eatenFood <= 20)
    {
        return 1000 - 50 * eat.eatenFood;
    }
    else
    {
        return 1;
    }
}

int main()
{
    char matrix[MAX_X][MAX_Y];
    struct snake_t snake = initSnake(7, 7, 2);
    struct eat eat = initEat();

    fillMatrix(matrix, &snake, eat);
    printMatrix(matrix, eat);
    printLevel(eat);
    int key = LEFT;
    while (1)
    {
        clock_t begin = clock();
        if (kbhit())
        {
            key = keyProcessing(snake, key, eat);
        }
        snake = moveSnake(snake, key);
        selfEating(snake, eat);
        grownSnake(&snake, eat);
        eat = transferEat(eat, snake, matrix);
        Sleep(speedBoost(eat));
        fillMatrix(matrix, &snake, eat);
        system("cls");
        printMatrix(matrix, eat);
        printLevel(eat);
    }

    return 0;
}