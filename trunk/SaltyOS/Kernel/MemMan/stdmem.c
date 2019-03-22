#include "Kernel\Common\KCommon.h"
#include "Kernel\Common\BugCheck.h"
#include "Kernel\MemMan\MemMan.h"
#include <stdlib.h>
#include <string.h>

//redirects malloc and free to our own ones.

_PTR malloc(size_t size)
{
	return MemMan_malloc(size);
}

_VOID free(_PTR ptr)
{
	MemMan_free(ptr);
}

_PTR realloc(_PTR p1, size_t p2)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return NULL;
}

_PTR calloc(size_t p1, size_t p2)
{
	void* Ptr = MemMan_malloc(p1 * p2);
	memset(Ptr, 0, p1 * p2);
	return Ptr;
}

_PTR memalign(size_t p1, size_t p2)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return NULL;
}

//don't know how to declare. struct mallinfo and function mallinfo have the same name.
/*struct mallinfo mallinfo(void)
{
	mallinfo v1;
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return v1;
}*/

void malloc_stats(void)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
}

int mallopt(int p1, int p2)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return 0;
}

size_t malloc_usable_size(_PTR p1)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return 0;
}

_PTR valloc(size_t p1)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return NULL;
}

_PTR pvalloc(size_t p1)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return NULL;
}

int malloc_trim(size_t p1)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
	return 0;
}

_VOID mstats(char * p1)
{
	BugCheck(InvalidCall, 0, 0, 0, 0);
}
