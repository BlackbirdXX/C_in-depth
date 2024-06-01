/*
Напишите программу, которая находит разницу между максимальным и минимальным элементом в дереве.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int key;
    struct node *left, *right, *root;
} node;


node *getNode(int value, node *root);                           // Вспомогательная функция создания ноды
void pushNode(int value, node **tree);                          // Функция вставки ноды в дерево.
void printTreeDFS(node *tree, const char *dir, int level);      // Функция печати дерева. 
int sumNode(node *tree);                                        // Функция подсчета суммы значений всех нод в дереве.
int getMinNode(node *root);                                     // Функция поиска минимального значения в дереве.
int getMaxNode(node *root);                                     // Функция поиска максимального значения в дереве.


int main(int argc, char const *argv[])
{
    int n[] = {10, 1, 3, 5, 7, 6, 15, 13, 18};
    node *tree = NULL;
    for (int i = 0; i < 9; i++)
    {
        pushNode(n[i], &tree);
    }
    printTreeDFS(tree, "Root", 0);
    printf("MAX - MIN = %d ", getMaxNode(tree) - getMinNode(tree));
    return 0;
}

node *getNode(int value, node *root)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->key = value;
    tmp->left = tmp->right = NULL;
    tmp->root = root;
    return tmp;
}

void pushNode(int value, node **tree)
{
    node *tmp = NULL;
    node *insert = NULL;
    if (*tree == NULL)
    {
        *tree = getNode(value, NULL);
        return;
    }
    tmp = *tree;
    while (tmp)
    {
        if (value > tmp->key)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = getNode(value, tmp);
                return;
            }
        }
        else if (value < tmp->key)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = getNode(value, tmp);
                return;
            }
        }
    }
}

void printTreeDFS(node *tree, const char *dir, int level)
{
    if (tree) {
        printf("lvl %d %s = %d\n", level, dir, tree->key);
        printTreeDFS(tree->left, "left", level+1);
        printTreeDFS(tree->right, "right", level+1);
    }
}

int sumNode(node *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return tree->key + sumNode(tree->left) + sumNode(tree->right);
}

int getMinNode(node *root) {
    while (root->left) {
        root = root->left;
    }
    return root->key;
}

int getMaxNode(node *root) {
    while (root->right) {
        root = root->right;
    }
    return root->key;
}