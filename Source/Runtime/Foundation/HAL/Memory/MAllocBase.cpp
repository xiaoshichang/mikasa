#include "MAllocBase.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

MallocBase* MallocOperation::GlobalAllocator = nullptr;

void *MallocOperation::operator new(size_t size)
{
    MIKASA_ASSERT(GlobalAllocator != nullptr);
    return GlobalAllocator->Malloc(size);
}

void MallocOperation::operator delete(void *origin)
{
    MIKASA_ASSERT(GlobalAllocator != nullptr);
    GlobalAllocator->Free(origin);
}

void *MallocOperation::operator new[](size_t size)
{
    MIKASA_ASSERT(GlobalAllocator != nullptr);
    return GlobalAllocator->Malloc(size);
}

void MallocOperation::operator delete[](void *origin)
{
    MIKASA_ASSERT(GlobalAllocator != nullptr);
    GlobalAllocator->Free(origin);
}
