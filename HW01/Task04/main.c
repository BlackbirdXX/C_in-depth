#include <stdio.h>

int main (void)
{
    int key = 0;
    char string_in = ' ', string_out = ' ';
    printf("Enter key = ");
    scanf("%d ", &key);
    printf("Enter string : ");
    while (string_in != '.') 
    {
        string_in = getchar();
        if (string_in >= 'a' && string_in <= 'z') {
            string_out = (key + string_in - 'a') % 26 + 'a';
        } 
        else {
            if (string_in >= 'A' && string_in <= 'Z') {
                string_out = (key + string_in - 'A') % 26 + 'A';
            }
            else {
                string_out = string_in;
            }
        }
        putchar(string_out);
    }
    return 0;
}
