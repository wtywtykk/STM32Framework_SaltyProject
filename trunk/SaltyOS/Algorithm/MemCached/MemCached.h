#pragma once

#include "Kernel\Common\KCommon.h"
#include <assert.h>

#define MemCachedMaxElementSize sizeof(u32)
#define MemCachedBlockCount 4
#define MemCachedBlockElementCount 512
#define MemCachedBlockSize (MemCachedMaxElementSize*MemCachedBlockElementCount)

typedef void(*MemCachedLoadFunc)(u32 StorageAddr, void* MemCachedAddr, u32 Size);
typedef void(*MemCachedStoreFunc)(void* MemCachedAddr, u32 StorageAddr, u32 Size);

template <class T> class MemCachedObject
{
private:
	u8 LastUsedBuffer;
	u32 MaxIndex;
	struct __tag_MemCachedBlock
	{
		u8 Buffer[MemCachedBlockSize];
		u32 LowerBound;
		u32 UpperBound;
	}Cache[MemCachedBlockCount];

	MemCachedLoadFunc Load = NULL;
	MemCachedStoreFunc Store = NULL;

	MemCachedObject(const MemCachedObject& Obj);
	MemCachedObject& operator=(const MemCachedObject&);
public:
	MemCachedObject(void);
	MemCachedObject(MemCachedLoadFunc LoadFunc, MemCachedStoreFunc StoreFunc, u32 Size);
	~MemCachedObject(void);
	void Attach(MemCachedLoadFunc LoadFunc, MemCachedStoreFunc StoreFunc, u32 Size);
	void Sync(void);
	T& operator[](u32 Index);
	void Flush(void);
	void Detach(void);
};

//Copying is forbidden
template <class T> inline MemCachedObject<T>::MemCachedObject(const MemCachedObject& Obj)
{
}

template <class T> inline MemCachedObject<T> & MemCachedObject<T>::operator=(const MemCachedObject<T> &)
{
	return *this;
}

template <class T> inline MemCachedObject<T>::MemCachedObject(void)
{
	LastUsedBuffer = 0;
	MaxIndex = 0;
	for (u32 i = 0; i < MemCachedBlockCount; i++)
	{
		Cache[i].LowerBound = 0;
		Cache[i].UpperBound = 0;
	}
	Load = NULL;
	Store = NULL;
}

template <class T> inline MemCachedObject<T>::MemCachedObject(MemCachedLoadFunc LoadFunc, MemCachedStoreFunc StoreFunc, u32 Size)
{
	Load = NULL;
	Store = NULL;
	Attach(LoadFunc, StoreFunc, Size);
}

template <class T> inline MemCachedObject<T>::~MemCachedObject(void)
{
	Detach();
}

template<class T> inline void MemCachedObject<T>::Attach(MemCachedLoadFunc LoadFunc, MemCachedStoreFunc StoreFunc, u32 Size)
{
	if (Load || Store)
	{
		Detach();
	}
	LastUsedBuffer = 0;
	MaxIndex = Size;
	for (u32 i = 0; i < MemCachedBlockCount; i++)
	{
		Cache[i].LowerBound = 0;
		Cache[i].UpperBound = 0;
	}
	Load = LoadFunc;
	Store = StoreFunc;
}

template<class T> inline void MemCachedObject<T>::Sync(void)
{
	LastUsedBuffer = 0;
	for (u32 i = 0; i < MemCachedBlockCount; i++)
	{
		Cache[i].LowerBound = 0;
		Cache[i].UpperBound = 0;
	}
}

template<class T> inline T & MemCachedObject<T>::operator[](u32 Index)
{
	assert(Index < MaxIndex);
	assert(sizeof(T) <= MemCachedMaxElementSize);
	if (Load || Store)
	{
		u8 i = 0;
		for (; i < MemCachedBlockCount; i++)
		{
			if (Cache[i].LowerBound <= Index && Index < Cache[i].UpperBound)
			{
				break;
			}
		}
		if (i == MemCachedBlockCount)
		{
			u32 NewBlockLowerBound = Index / (MemCachedBlockSize / sizeof(T)) * (MemCachedBlockSize / sizeof(T));
			u32 NewBlockUpperBound = NewBlockLowerBound + (MemCachedBlockSize / sizeof(T));
			if (NewBlockUpperBound > MaxIndex)
			{
				NewBlockUpperBound = MaxIndex;
			}
			i = LastUsedBuffer + 1;
			i %= MemCachedBlockCount;
			if (Cache[i].UpperBound != Cache[i].LowerBound && Store)
			{
				Store(Cache[i].Buffer, Cache[i].LowerBound, Cache[i].UpperBound - Cache[i].LowerBound);
			}
			Cache[i].LowerBound = NewBlockLowerBound;
			Cache[i].UpperBound = NewBlockUpperBound;
			if (Load)
			{
				Load(Cache[i].LowerBound, Cache[i].Buffer, Cache[i].UpperBound - Cache[i].LowerBound);
			}
		}
		LastUsedBuffer = i;
		return *((T*)&Cache[i].Buffer[(Index - Cache[i].LowerBound) * sizeof(T)]);
	}
	else
	{
		return *((T*)&Cache[0].Buffer[0]);
	}
}

template<class T> inline void MemCachedObject<T>::Flush(void)
{
	if (Store)
	{
		for (u32 i = 0; i < MemCachedBlockCount; i++)
		{
			if (Cache[i].UpperBound != Cache[i].LowerBound)
			{
				Store(Cache[i].Buffer, Cache[i].LowerBound, Cache[i].UpperBound - Cache[i].LowerBound);
			}
		}
	}
}

template<class T> inline void MemCachedObject<T>::Detach(void)
{
	Flush();
	Load = NULL;
	Store = NULL;
}
