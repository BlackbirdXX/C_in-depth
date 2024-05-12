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
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define CYAN FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define YELLOW FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define WHITE FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

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
    char color;
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

void setSnakeColor(struct snake_t *snake)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    char cch;
    while (1)
    {
        SetConsoleTextAttribute(hStdOut, RED);
        printf("1 : Red\n");
        SetConsoleTextAttribute(hStdOut, BLUE);
        printf("2 : Blue\n");
        SetConsoleTextAttribute(hStdOut, GREEN);
        printf("3 : Green\n");
        SetConsoleTextAttribute(hStdOut, CYAN);
        printf("4 : Cyan\n");
        SetConsoleTextAttribute(hStdOut, YELLOW);
        printf("5 : Yellow\n");
        SetConsoleTextAttribute(hStdOut, RESETDEV);

        cch = getch();
        if (cch == '1')
        {
            snake->color = RED;
            break;
        }
        else if (cch == '2')
        {
            snake->color = BLUE;
            break;
        }
        else if (cch == '3')
        {
            snake->color = GREEN;
            break;
        }
        else if (cch == '4')
        {
            snake->color = CYAN;
            break;
        }
        else if (cch == '5')
        {
            snake->color = YELLOW;
            break;
        }
        else
        {
            printf("Enter the number of the mode (1 or 2)\n");
        }
    }
}

// Перекладывание еды на новое место. С учетом свободного места на карте. Одиночная игра.
eat transferEatSingleGame(eat eat, snake_t snake1, char matrix[MAX_X][MAX_Y])
{
    if (((snake1.x == eat.x) && (snake1.y == eat.y)))
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
// Перекладывание еды на новое место. С учетом свободного места на карте. Игра с ИИ
eat transferEatAiGame(eat eat, snake_t snake1, snake_t snake2, char matrix[MAX_X][MAX_Y])
{
    if (((snake1.x == eat.x) && (snake1.y == eat.y)) || ((snake2.x == eat.x) && (snake2.y == eat.y)))
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
    snake.color = WHITE;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; ++i)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

char startMenu()
{
    printf("     SNAKE     \n");
    printf("Mode selection \n");
    printf("1 - Single mode \n");
    printf("2 - Competition mode \n");
    printf("Enter your choice : \n");
    char sch;

    while (1)
    {
        if (((sch = getch()) == '1') || ((sch = getch()) == '2'))
        {
            break;
        }
        else
        {
            printf("Enter the number of the mode (1 or 2)\n");
        }
    }
    return sch;
}

// Функция заполнения матрицы для одиночной игры
void fillMatrixSingleGame(char matrix[MAX_X][MAX_Y], struct snake_t *snake1, eat eat)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
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
    matrix[snake1->x][snake1->y] = '@';
    for (int i = 0; i < snake1->tsize; i++)
    {
        matrix[snake1->tail[i].x][snake1->tail[i].y] = '*';
    }

    matrix[eat.x][eat.y] = 'o';
}

// Функция заполнения матрицы для игры с ИИ
void fillMatrixAiGame(char matrix[MAX_X][MAX_Y], struct snake_t *snake1, struct snake_t *snake2, eat eat)
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
    matrix[snake1->x][snake1->y] = '@';
    for (int i = 0; i < snake1->tsize; i++)
    {
        matrix[snake1->tail[i].x][snake1->tail[i].y] = '*';
    }
    matrix[snake2->x][snake2->y] = '#';
    for (int i = 0; i < snake2->tsize; i++)
    {
        matrix[snake2->tail[i].x][snake2->tail[i].y] = '.';
    }
    matrix[eat.x][eat.y] = 'o';
}

// Функция печати заполненой матрицы. Одиночная игра.
void printMatrixSingleGame(char matrix[MAX_X][MAX_Y], struct snake_t *snake1, eat eat)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            if (j == eat.y && i == eat.x)
            {
                SetConsoleTextAttribute(hStdOut, GREEN);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if (j == snake1->y && i == snake1->x)
            {
                SetConsoleTextAttribute(hStdOut, snake1->color);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }

            else
            {
                printf("%c", matrix[i][j]);
            }
        }
        printf("\n");
    }
}
// Функция печати заполненой матрицы. Игра с ИИ.
void printMatrixAiGame(char matrix[MAX_X][MAX_Y], struct snake_t *snake1, struct snake_t *snake2, eat eat)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            if (j == eat.y && i == eat.x)
            {
                SetConsoleTextAttribute(hStdOut, GREEN);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if (j == snake1->y && i == snake1->x)
            {
                SetConsoleTextAttribute(hStdOut, snake1->color);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if (j == snake2->y && i == snake2->x)
            {
                SetConsoleTextAttribute(hStdOut, snake2->color);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else
            {
                printf("%c", matrix[i][j]);
            }
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

snake_t moveSnakeII(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    if (snake.direction == LEFT)
    {
        snake.x = snake.x - 1;
        if (snake.x < MIN_X)
        {
            snake.x = MAX_X - 1;
        }
        snake.direction = LEFT;
    }
    else if (snake.direction == UP)
    {
        snake.y = snake.y - 1;
        if (snake.y < MIN_Y)
        {
            snake.y = MAX_Y - 1;
        }
        snake.direction = UP;
    }
    else if (snake.direction == RIGHT)
    {
        snake.x = snake.x + 1;
        if (snake.x > MAX_X - 1)
        {
            snake.x = MIN_X;
        }
        snake.direction = RIGHT;
    }
    else if (snake.direction == DOWN)
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

// Конец игры, если змейка укусила сама себя. Одиночная игра.
void selfEatingSingleGame(snake_t snake1, eat eat)
{
    for (int i = snake1.tsize - 1; i > 0; i--)
    {
        if (snake1.x == snake1.tail[i].x && snake1.y == snake1.tail[i].y)
        {
            system("cls");
            for (int i = 0; i < MAX_X; ++i)
            {
                if (i == 7)
                {
                    printf("         GAME OVER           \n");
                    printf("     The Snake 1 lost.       \n");
                    printf("___________Result____________\n");
                    printf("Level : %d  \nSnake 1 : %d meters", eat.eatenFood, snake1.tsize);
                }
                printf("               \n");
            }
            free(snake1.tail);
            sleep(3);
            exit(0);
        }
    }
}

// Конец игры, если змейка укусила сама себя игра с ИИ.
void selfEatingAiGame(snake_t snake1, snake_t snake2, eat eat)
{
    for (int i = snake1.tsize - 1; i > 0; i--)
    {
        if (snake1.x == snake1.tail[i].x && snake1.y == snake1.tail[i].y)
        {
            system("cls");
            for (int i = 0; i < MAX_X; ++i)
            {
                if (i == 7)
                {
                    printf("         GAME OVER           \n");
                    printf("     The Snake 1 lost.       \n");
                    printf("___________Result____________\n");
                    printf("Level : %d  \nSnake 1 : %d meters\nSnake 2 : %d meters", eat.eatenFood, snake1.tsize, snake2.tsize);
                }
                printf("               \n");
            }
            free(snake1.tail);
            free(snake2.tail);
            sleep(3);
            exit(0);
        }
    }
    for (int i = snake2.tsize - 1; i > 0; i--)
    {
        if (snake2.x == snake2.tail[i].x && snake2.y == snake2.tail[i].y)
        {
            system("cls");
            for (int i = 0; i < MAX_X; ++i)
            {
                if (i == 7)
                {
                    printf("         GAME OVER           \n");
                    printf("     The Snake 2 lost.       \n");
                    printf("___________Result____________\n");
                    printf("Level : %d  \nSnake 1 : %d meters\nSnake 2 : %d meters", eat.eatenFood, snake1.tsize, snake2.tsize);
                }
                printf("               \n");
            }
            free(snake1.tail);
            free(snake2.tail);
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

void autoChangeDirection(snake_t *snake, struct eat eat)
{

    if ((snake->direction == RIGHT || snake->direction == LEFT) && (snake->y != eat.y)) // горизонтальное движение
    {
        snake->direction = (eat.y > snake->y) ? DOWN : UP;
    }
    else if ((snake->direction == DOWN || snake->direction == UP) && (snake->x != eat.x)) // вертикальное движение
    {
        snake->direction = (eat.x > snake->x) ? RIGHT : LEFT;
    }
}

void singleGame()
{
    char matrix[MAX_X][MAX_Y];
    struct snake_t snake1 = initSnake(7, 7, 2);
    printf("Choose the color of the snake :\n");
    setSnakeColor(&snake1);
    struct eat eat = initEat();

    fillMatrixSingleGame(matrix, &snake1, eat);
    printMatrixSingleGame(matrix, &snake1, eat);
    printLevel(eat);
    int key = LEFT;
    while (1)
    {
        clock_t begin = clock();
        if (kbhit())
        {
            key = keyProcessing(snake1, key, eat);
        }
        snake1 = moveSnake(snake1, key);
        selfEatingSingleGame(snake1, eat);
        grownSnake(&snake1, eat);
        eat = transferEatSingleGame(eat, snake1, matrix);
        Sleep(speedBoost(eat));
        fillMatrixSingleGame(matrix, &snake1, eat);
        system("cls");
        printMatrixSingleGame(matrix, &snake1, eat);
        printLevel(eat);
    }
}

void playerVsAiGame()
{
    char matrix[MAX_X][MAX_Y];
    struct snake_t snake1 = initSnake(7, 7, 2);
    printf("Choose the color of the snake 1 :\n");
    setSnakeColor(&snake1);
    struct snake_t snake2 = initSnake(3, 10, 2);
    printf("Choose the color of the snake 2 :\n");
    setSnakeColor(&snake2);
    struct eat eat = initEat();

    fillMatrixAiGame(matrix, &snake1, &snake2, eat);
    printMatrixAiGame(matrix, &snake1, &snake2, eat);
    printLevel(eat);
    int key = LEFT;
    while (1)
    {
        clock_t begin = clock();
        if (kbhit())
        {
            key = keyProcessing(snake1, key, eat);
        }
        snake1 = moveSnake(snake1, key);
        autoChangeDirection(&snake2, eat);
        snake2 = moveSnakeII(snake2);
        selfEatingAiGame(snake1, snake2, eat);
        grownSnake(&snake1, eat);
        grownSnake(&snake2, eat);
        eat = transferEatAiGame(eat, snake1, snake2, matrix);
        Sleep(speedBoost(eat));
        fillMatrixAiGame(matrix, &snake1, &snake2, eat);
        system("cls");
        printMatrixAiGame(matrix, &snake1, &snake2, eat);
        printLevel(eat);
    }
}

int main()
{
    char startChoice = startMenu();
    switch (startChoice)
    {
    case '1':
        singleGame();
        break;

    case '2':
        playerVsAiGame();
        break;
    default:
        break;
    }

    return 0;
}