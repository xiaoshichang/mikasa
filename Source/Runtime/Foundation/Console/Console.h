#pragma once
#include <string>
#include "../MultiThread.h"

namespace mikasa::Runtime::Foundation
{
    enum ConsoleTextColor
    {
        White,
        Yellow,
        LightGreen,
        LightRed
    };

    class Console
    {
    public:
        explicit Console();
        virtual ~Console();

    public:
        virtual void OutputString(const std::string& s, ConsoleTextColor color) = 0;
        virtual bool GetReadyInputString(std::string& ret) = 0;
        virtual void InputPrefix() = 0;
        virtual void ProcessInputEvents() = 0;
        virtual void SetOffset(int x, int y) = 0;

    protected:
        const std::string PREFIX = ">>> ";


    public:
        static void Init();
        static void UnInit();
        static Console* GetInstance();

    public:
        static CriticalSection ConsoleProtection;

    private:
        static Console* Instance_;
        static RunnableThread* InputThread_;
        static Runnable* InputRunnable_;

    };

}

