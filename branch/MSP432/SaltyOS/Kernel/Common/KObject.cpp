#include "KCommon.h"
#include "KObject.h"
#include <assert.h>

//Copying is forbidden
KOBJECT::KOBJECT(const KOBJECT& Obj)
{
}

KOBJECT & KOBJECT::operator=(const KOBJECT &)
{
	return *this;
}

KOBJECT::KOBJECT(void)
{
	RefCount = 0;
	StaticObject = false;
}

KOBJECT::~KOBJECT(void)
{
	assert(RefCount == 0);
	assert(StaticObject == false);
}

void KOBJECT::MarkObjectStatic(void)
{
	StaticObject = true;
}

KOBJECT* KOBJECT::NewReference(void)
{
	RefCount++;
	return this;
}

void KOBJECT::FreeReference(void)
{
	assert(RefCount > 0);
	RefCount--;
	if (RefCount == 0 && !StaticObject)
	{
		delete this;
	}
}
