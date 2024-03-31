#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t N;
	printf("Enter a number N\n");
	scanf("%d", &N);
	uint32_t count = 0;
	uint32_t max = 0;
	uint32_t temp = 0;
	printf("Enter the numbers one at a time\n");
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &temp);
		if (temp > max)
		{
			max = temp;
			count = 1;
		}
		else if (temp == max)
		{
			count++;
		}
	}
	
	printf("%u\n", count);
	return 0;
}