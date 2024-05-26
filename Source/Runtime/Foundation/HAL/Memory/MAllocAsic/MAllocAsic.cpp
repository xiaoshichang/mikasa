#include <cstdlib>
#include "MAllocAsic.h"

using namespace mikasa::Runtime::Foundation;

void *MAllocAsic::Malloc(size_t size)
{
    auto ptr = malloc(size);
    return ptr;
}

void MAllocAsic::Free(void *origin)
{
    free(origin);
}

