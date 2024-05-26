#pragma once
#include "Runtime/Foundation/Foundation.h"
#include <cstddef>

namespace mikasa::Runtime::Foundation
{
    class MallocBase
    {
    public:
        virtual ~MallocBase() = default;
        virtual void* Malloc(size_t size) = 0;
        virtual void Free( void* Original ) = 0;
    };


    class MallocOperation
    {
    public:
        void* operator new(size_t Size);

        void operator delete(void* Ptr);

        void* operator new[](size_t Size);

        void operator delete[](void* Ptr);

    public:
        static MallocBase* GlobalAllocator;
    };
}
