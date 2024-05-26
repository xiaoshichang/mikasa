
#include "MemoryManagementModule.h"
#include "Runtime/Foundation/HAL/Memory/MAllocBase.h"
#include "Runtime/Foundation/HAL/Memory/MAllocAsic/MAllocAsic.h"

using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

void MemoryManagementModule::Init(const ApplicationInitParam &info)
{
    MallocOperation::GlobalAllocator = new MAllocAsic();
}

void MemoryManagementModule::UnInit()
{
    delete MallocOperation::GlobalAllocator;
}
