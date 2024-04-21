// Написать алгоритм перевода из инфиксной записи в обратную польскую. 
// Для его реализации нужны данные по приоритетам операций. 
// Реализовать алгоритм, используя побитовые операции (&, |, ^).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{
    char data;
    struct element* next;
} stack;

stack* Push(stack* top, char data)
{
    stack* ptr = malloc(sizeof(stack));
    if (ptr)
    {
        ptr->data = data;
        ptr->next = top;
    }
    return ptr;
}

stack* Pop(stack* top)
{
    if(top == NULL)
        return top;
    
    stack* ptr_next = top->next;
    free(top);
    return ptr_next;
}

char* FillString(char* str,int max_len)
{
    int i = 0;
    char ch;
    puts("Enter a string in the infix entry");
    puts("Important! Separate the characters with a space, and there must be a dot at the end.");
    puts("Example : 8 ^ 2 & 5 | ( 6 & 1 )");
    while ((ch = getchar()) != '.' && ch != EOF && i < max_len -1){
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}


int priority(char c)
{
    if(c == '&'){
        return 3;
    }
    if (c == '^')
    {
        return 2;
    }
    if (c == '|')
    {
        return 1;
    }
    return 0;
}

void translation(char * source, char* destination, stack* top){
    int len = strlen(source);
    char ch;
    int cursor = 0;
    for (size_t i = 0; i < len; i++)
    {
        ch = source[i];
        if (ch >= '0' && ch <= '9')
        {
            int num = 0, size = 0;
            for (num; source[i] >= '0' && source[i] <= '9'; i++, size ++)
            {
                num = num*10+source[i]-'0';
            }
            sprintf(destination+cursor,"%d ",num);
            cursor += size+1;
        }
        else
        {
            if(i >= len)
            {
                break;
            }
            
            if(ch == '&' || ch == '|' || ch == '^')
            {
                while (top != NULL)
                {
                    char temp = top->data;
                    top = Pop(top);
                    if(priority(temp) >= priority(ch))
                    {
                        sprintf(destination+cursor,"%c ",temp);
                        cursor +=2;
                    }
                    else
                    {
                        top = Push(top, temp);
                        break;
                    }
                }
                top = Push(top, ch);
            }
            else if (ch == '(')
            {
                top = Push(top, ch);
            }
            else if (ch == ')')
            {
                while ((ch = top->data) != '(')
                {
                    sprintf(destination+cursor, "%c ", ch);
                    cursor +=2;
                    top = Pop(top);
                }
            }
        }
    }
    while(top != NULL)
    {
        ch = top->data;
        top = Pop(top);
        if(ch != '(')
        {
        sprintf(destination+cursor, "%c ", ch);
        cursor +=2;
        }
    }
    
}

int main(int argc, char const *argv[])
{
    system("cls");
    stack* top = NULL;
    char staples[100];
    int max_len = sizeof(staples);
    char destination[max_len];
    FillString(staples, max_len);
    puts(staples);
    translation(staples, destination, top);
    printf("%s", destination);
    return 0;
}