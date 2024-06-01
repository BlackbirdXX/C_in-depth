/*
Задание 1. Поиск первого и последнего слова

Используя код задачи 1, написать программу поиска первого и последнего слова в строке.

Пример №1
Данные на входе: efg abcd zzz.
Данные на выходе: efg zzz.

Пример №2
Данные на входе: fffff kkkkkk a.
Данные на выходе: fffff a.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *word;
    struct node *next;
} node;

void printList(node *list)
{
    node *ptr = list;
    char *lastWord = ptr->word;
    ptr = ptr->next;
    while (ptr != NULL)
    {
        if (ptr->next == NULL)
        {
            printf("First word : %s \n", ptr->word);
        }
        ptr = ptr->next;
    }
    printf("Last word : %s \n", lastWord);
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

node *insert(char *word, node *head)
{
    node *res = (node *)calloc(1, sizeof(node));
    int len = strlen(word);
    res->word = malloc(len + 1);
    strcpy(res->word, word);
    res->next = head;
    return res;
}

int main()
{
    node *list = NULL;
    char example[] = {"fffff efg abcd zzz kkkkkk a"};
    char *del = " ";
    char *token = strtok(example, del);

    while (token)
    {
        list = insert(token, list);
        token = strtok(NULL, del);
    }

    printList(list);
    deleteList(list);
    getchar();
    return 0;
}