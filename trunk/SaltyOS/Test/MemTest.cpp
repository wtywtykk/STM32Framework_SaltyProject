#include "Kernel\Common\KCommon.h"
#include <stdlib.h>
#include <string.h>

#define testcount 30
void MemTest(void)
{
	void* MemoryBlocks[testcount];
	memset(MemoryBlocks, 0, sizeof(MemoryBlocks));
	while (1)
	{
		u8 Index = (rand() - 1) * testcount / RAND_MAX;
		if (rand() > RAND_MAX / 2)
		{
			if (MemoryBlocks[Index] == NULL)
			{
				u16 msize = rand() * 500 / RAND_MAX;
				MemoryBlocks[Index] = malloc(msize);
			}
		}
		else
		{
			if (MemoryBlocks[Index])
			{
				free(MemoryBlocks[Index]);
				MemoryBlocks[Index] = NULL;
			}
		}
	}
}
