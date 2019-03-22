#pragma once

#include "KCommon.h"

typedef void(*CLEANUPFUNC)(void* Object);

class KOBJECT
{
private:
	u16 RefCount;
	bool StaticObject;
	KOBJECT(const KOBJECT& Obj);
	KOBJECT& operator=(const KOBJECT&);
public:
	KOBJECT(void);
	virtual ~KOBJECT(void);
	void MarkObjectStatic(void);
	KOBJECT* NewReference(void);
	void FreeReference(void);
};

template<typename T>
T NewReferenceSafe(T Obj)
{
	if (Obj)
	{
		return (T)Obj->NewReference();
	}
	else
	{
		return NULL;
	}
}

template<typename T>
void FreeAndEraseReference(T& Ref)
{
	if (Ref)
	{
		Ref->FreeReference();
		Ref = NULL;
	}
}
