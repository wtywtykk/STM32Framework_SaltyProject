#include "Kernel\Common\KCommon.h"
#include "Kernel\Common\BugCheck.h"
#include "HAL\Interrupt.h"
#include "Kernel\MemMan\Pool.h"
#include <assert.h>

typedef struct MemBlock
{
	u32 PrevGuard;
	struct MemBlock* Prev;
	struct MemBlock* Next;
	u32 Size;
	bool Free;
	u32 PostGuard;
}MemBlock;

void EnterMemoryCriticalSetion(void)
{
	DisableInterrupt();
}

void LeaveMemoryCriticalSection(void)
{
	EnableInterrupt();
}

u32 Pool_RoundUpValueToAlignment(u32 Val)
{
	if (Val & POOL_INVALIDBITS)
	{
		return (Val & ~POOL_INVALIDBITS) + POOL_ALIGNMENT;
	}
	return Val;
}

u32 Pool_CalcGuardKey(u32* Addr)
{
	return (((u32)Addr) ^ 0xBADC0FFE);
}

void Pool_CheckIntegrity(MemBlock* Block)
{
	if (Block->PrevGuard != Pool_CalcGuardKey(&Block->PrevGuard) || Block->PostGuard != Pool_CalcGuardKey(&Block->PostGuard))
	{
		BugCheck(MemoryCorruption, (u32)Block, 0, 0, 0);
	}
}

void Pool_CheckIntegrity_Full(MemBlock* Pool)
{
	if (Pool)
	{
		MemBlock* Ptr = Pool;
		do
		{
			Pool_CheckIntegrity(Ptr);
			if (Ptr->Next)
			{
				if (Ptr->Next->Prev != Ptr)
				{
					BugCheck(MemoryCorruption, (u32)Ptr->Next, 0, 0, 0);
				}
			}
			Ptr = Ptr->Next;
		} while (Ptr);
		Ptr = Pool;
		do
		{
			Pool_CheckIntegrity(Ptr);
			if (Ptr->Prev)
			{
				if (Ptr->Prev->Next != Ptr)
				{
					BugCheck(MemoryCorruption, (u32)Ptr->Prev, 0, 0, 0);
				}
			}
			Ptr = Ptr->Prev;
		} while (Ptr);
	}
}

STATUS Pool_Init(void* Pool, u32 Size)
{
	MemBlock* Block = (MemBlock*)Pool;
	if (Size < sizeof(MemBlock) * 10)
	{
		return S_FAIL;
	}
	static_assert(sizeof(MemBlock) % POOL_ALIGNMENT == 0, "The size of MemBlock must be aligned to POOL_ALIGNMENT");
	assert((u32)Pool % POOL_ALIGNMENT == 0);
	Pool = (void*)Pool_RoundUpValueToAlignment((u32)Pool);

	Block->Prev = NULL;
	Block->Next = NULL;
	Block->Size = Size;
	Block->Free = true;
	Block->PrevGuard = Pool_CalcGuardKey(&Block->PrevGuard);
	Block->PostGuard = Pool_CalcGuardKey(&Block->PostGuard);

	return S_OK;
}

void* Pool_Alloc(void* Pool, u32 Size)
{
	MemBlock* Block;
	void* Ret = NULL;
	EnterMemoryCriticalSetion();

	assert((u32)Pool % POOL_ALIGNMENT == 0);
	Pool = (void*)Pool_RoundUpValueToAlignment((u32)Pool);
	Size = Pool_RoundUpValueToAlignment(Size);
	Block = (MemBlock*)Pool;
#ifdef DEBUG
	Pool_CheckIntegrity_Full((MemBlock*)Pool);
#endif
	while (Block)
	{
		if (!Block->Free || Block->Size < Size)
		{
			Block = Block->Next;
		}
		else
		{
			if (Block->Size >= Size)
			{
				if (Block->Size > Size + sizeof(MemBlock) * 2)
				{
					MemBlock* NewBlock = (MemBlock*)(((u8*)Block) + sizeof(MemBlock) + Size);
					NewBlock->Free = true;
					NewBlock->Next = Block->Next;
					NewBlock->Prev = Block;
					NewBlock->Size = Block->Size - sizeof(MemBlock) - Size;
					NewBlock->PrevGuard = Pool_CalcGuardKey(&NewBlock->PrevGuard);
					NewBlock->PostGuard = Pool_CalcGuardKey(&NewBlock->PostGuard);
					if (Block->Next)
					{
						Block->Next->Prev = NewBlock;
					}
					Block->Next = NewBlock;
					Block->Size = Size;
				}
			}
			Block->Free = false;
			Block->PrevGuard = Pool_CalcGuardKey(&Block->PrevGuard);
			Block->PostGuard = Pool_CalcGuardKey(&Block->PostGuard);
			Ret = Block + 1;
			break;
		}
	}
#ifdef DEBUG
	Pool_CheckIntegrity_Full((MemBlock*)Pool);
#endif
	LeaveMemoryCriticalSection();
	return Ret;
}

void Pool_Free(void* Ptr)
{
	if (Ptr == NULL)
	{
		return;
	}
	assert((u32)Ptr % POOL_ALIGNMENT == 0);

	MemBlock* Block = ((MemBlock*)Ptr) - 1;
	EnterMemoryCriticalSetion();
#ifdef DEBUG
	MemBlock* PoolStart = Block;
	while (PoolStart->Prev)
	{
		PoolStart = PoolStart->Prev;
	}
	Pool_CheckIntegrity_Full(Block);
#endif
	Pool_CheckIntegrity(Block);
	if (Block->Prev && Block->Prev->Free)
	{
		if (Block->Next && Block->Next->Free)
		{
			Block->Prev->Size += sizeof(MemBlock) + Block->Size + sizeof(MemBlock) + Block->Next->Size;
			Block->Prev->Next = Block->Next->Next;
			if (Block->Next->Next)
			{
				Block->Next->Next->Prev = Block->Prev;
			}
		}
		else
		{
			Block->Prev->Size += sizeof(MemBlock) + Block->Size;
			Block->Prev->Next = Block->Next;
			if (Block->Next)
			{
				Block->Next->Prev = Block->Prev;
			}
		}
	}
	else
	{
		if (Block->Next && Block->Next->Free)
		{
			Block->Size += sizeof(MemBlock) + Block->Next->Size;
			Block->Free = true;
			Block->Next = Block->Next->Next;
			if (Block->Next)
			{
				Block->Next->Prev = Block;
			}
		}
		else
		{
			Block->Free = true;
		}
	}
#ifdef DEBUG
	Pool_CheckIntegrity_Full(PoolStart);
#endif
	LeaveMemoryCriticalSection();
}
