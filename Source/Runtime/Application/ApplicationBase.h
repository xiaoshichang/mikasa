#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;

namespace mikasa
{
    namespace Runtime
    {
        namespace Application
        {
            class ApplicationBase
            {
            public:
                virtual void Init(const ApplicationInitParam& info);
                virtual void UnInit();
                void Run();

            protected:
                void TryQuit();

            private:
                bool IsApplicationQuit_ = false;
            };
        }
    }
}





