#pragma once

#include "../MAllocBase.h"

namespace mikasa::Runtime::Foundation
{
    class MAllocAsic : public MallocBase
    {
    public:
        ~MAllocAsic() override = default;
        void* Malloc(size_t size) override;
        void Free( void* Original) override;
    };

}
