#pragma once
#include "Runtime/Application/ApplicationBase.h"

namespace mikasa
{
    namespace Runtime
    {
        namespace Application
        {
            class WindowsApplication : public ApplicationBase
            {
            public:
                void Init(const ApplicationInitParam& info) override;
                void UnInit() override;
            };
        }
    }
}

