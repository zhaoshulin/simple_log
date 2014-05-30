#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE * fp = NULL;
	fp = fopen("test.bin", "ab+");
	if(NULL == fp)
	{
		printf("Error: fopen failed!\n");
		return -1;
	}
	
	int txf[] = {1,2,3,4,5};
	fwrite(txf, sizeof(txf), 1, fp);
	return 0;
}
