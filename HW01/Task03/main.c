#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 
int main (void) {
    uint32_t n, b, temp = 0;
    printf("Enter n = ");
    scanf("%u", &n); 
    printf("Enter the numbers one at a time :\n");
    for (size_t i = 0; i < n; i++)
    {
        scanf("%u", &b);
        temp ^= b;
    }
    printf("\n%u\n",temp); 
 
    return 0;
}