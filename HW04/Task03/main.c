// Задание 3. Префикс и суффикс
// Реализовать программу 3-го практического задания более эффективным способом со сложностью О(n) (см. код в лекции).

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

enum
{
    maxlength = 10001
};
int search_prefix(char *, char *);

int main()
{
    system("cls");
    char s1[maxlength], s2[maxlength];
    puts("Enter string 1 :");
    scanf("%10001s", s1);
    puts("Enter string 2 :");
    scanf("%10001s", s2);
    // char s1[maxlength] = {"don't_panicdonnick_is"};     //Строка для тестов
    // char s2[maxlength] = {"nick_is_a_mastodonddon't_"}; //Строка для тестов
    printf("%d %d\n", search_prefix(s1, s2), search_prefix(s2, s1));
    return 0;
}

int search_prefix(char *s1, char *s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int i1, i2, max = 0, count = 0;
    char c1, c2;
    for (i1 = 0, i2 = 0; i1 < l1; i2++)
    {
        c1 = s1[i1];
        c2 = s2[i2];
        if (c1 == c2)              // Сравниваем два символа, если равны, 
        {
            i1++;                  // двигаем префикс на следующий знак
            count += 1;            // сохраняем в счетчик
        }
        if(c1 != c2 && count > 0)  // Если символы не равны, и счетчик показывает то, что совпадения уже были
        {
            if (count > max)       // Если текущий счетчик больше максимального :
            {
                max = count;       // Делаем текущий максимальным
            }
            count = 0;             // И обнуляем его
            i1 = 0;                // Возвращаемся в начало префикса
            i2--;                  // Делаем задержку для позиции второй строки
        }
        if (count == l2)           // Это условие если строки одинаковые
        {
            max = count;
        }
        if (i2 >= l2)              // Это условие выхода из цикла.
        {
            break;
        }
    }
    return max;
}