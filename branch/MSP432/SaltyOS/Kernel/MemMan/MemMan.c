#include "Kernel\Common\KCommon.h"
#include "Kernel\MemMan\Pool.h"

u8 InternalPool[8 * 1024];
void* Pools[2] = { InternalPool,NULL };
u32 Sizes[2] = { sizeof(InternalPool),0 };

STATUS MemMan_Init(void)
{
	return Pool_Init(Pools[0], Sizes[0]);
}

STATUS MemMan_InitExtendedPool(void)
{
	return S_OK;
}

void* MemMan_malloc(u32 Size)
{
	u8 i = 0;
	for (i = 0; i < sizeof(Pools) / sizeof(void*); i++)
	{
		void* AllocatedMem = Pool_Alloc(Pools[i], Size);
		if (AllocatedMem)
		{
			return AllocatedMem;
		}
	}
	return NULL;
}

void MemMan_free(void* Ptr)
{
	Pool_Free(Ptr);
}
