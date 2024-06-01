/*
Напишите программу, которая удаляет из списка все элементы с нечетным порядковым номером.

Пример №1
Данные на входе: aa ss dd ff gg hh jj kk ll.
Данные на выходе: aa dd gg jj ll

Пример №2
Данные на входе: aa ss dd ff gg hh jj kk ll tt.
Данные на выходе: aa dd gg jj ll
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *word;
    int number;
    struct node *next;
} node;

void printList(node *list);                         // Функция вывода списка на экан.
void insert(char *word, node **head, int count);    // Функция добавления ноды в список.
node *findNode(node *head, int position);           // Функция поиска ноды по значению.
int quantityNode(node *head);                       // Функция подсчета колличества нод в списке.
void deleteNode(node **head, node *toRemove);       // Функция удаления конкретной ноды.
void deleteList(node *list);                        // Функция удаления всего списка.

int main()
{
    node *list = NULL;
    char example[] = {"11 22 33 44 55 66 77 88 99 10"};

    //Разбиение строки на отдельные части и заполнение списка
    int count = 1;
    char *del = " ";
    char *token = strtok(example, del);
    while (token)
    {
        insert(token, &list, count++);
        token = strtok(NULL, del);
    }
    printList(list);
    
    // Подчет количества нод в списке
    int quantity = quantityNode(list);

    // Удаление нечетных нод при помощи вспомогательных функций
    for (int i = 0; i <= quantity; i++)
    {
        if (i %2 !=0)
        {
            deleteNode(&list, findNode(list,i));
        }
    }
    
    printf("\n");
    printList(list);
    deleteList(list);
    getchar();
    return 0;
}

void insert(char *word, node **head, int count)
{
    node *res = calloc(1, sizeof(node));
    int len = strlen(word);
    res->word = malloc(len + 1);
    res->number = count;
    strcpy(res->word, word);
    if (*head == NULL)
    {
        *head = res;
    }
    else
    {
        node *p = *head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = res;
    }
}

void deleteList(node *list)
{
    node *c = list;
    node *n;
    while (c != NULL)
    {
        n = c->next;
        free(c->word);
        free(c);
        c = n;
    }
    printf("The list has been deleted\n");
}

void deleteNode(node **head, node *toRemove)
{
    if((*head) == toRemove)
    {
        *head = toRemove->next;
        free(toRemove);
        return;
    }
    node *ptr = *head;
    while (ptr != NULL && ptr->next !=toRemove)
    {
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        return;
    }
    ptr->next = toRemove->next;
    free(toRemove);
}

int quantityNode(node *head)
{
    node *ptr = head;
    int count = 0;
    while (ptr != NULL)
    {
        ptr = ptr->next;
        count++;
    }
    return count;
}

node *findNode(node *head, int position)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->number == position)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void printList(node *list)
{
    while (list != NULL)
    {
        printf("%s ", list->word);
        list = list->next;
    }
    printf("\n");
}