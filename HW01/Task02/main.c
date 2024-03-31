#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 
int invert (const int num, const int bit) {
    const int mask = 1 << bit;
    return (num & mask)? (num & ~mask) : (num | mask);
}
 
void PrintBin (int n) {
    printf("\n");
    for (int i=31; i>=0; --i) {
        printf("%d", (n & (1 << i))? 1 : 0);
        if (i%4 == 0) printf(" ");
    }
}
 
int main (void) {
    uint32_t n, b;
    printf("n = ");
    scanf("%u", &n); 
    PrintBin(n); 
    for (size_t i = 24; i < 32; i++)
    {
        n = invert(n, i);
    }
    PrintBin(n);
    printf("\n%u\n",n); 
 
    return 0;
}