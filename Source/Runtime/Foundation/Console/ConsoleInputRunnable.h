#pragma once
#include "../MultiThread.h"

namespace mikasa::Runtime::Foundation
{
    class Console;
    class ConsoleInputRunnable : public Runnable
    {
    public:
        explicit ConsoleInputRunnable(Console* console);
        ~ConsoleInputRunnable() override = default;

        bool Init() override;

        uint32 Run() override;

        void Exit() override;

        void Stop() override;

    private:
        bool Running_ = true;
        Console* Console_;
    };

}
