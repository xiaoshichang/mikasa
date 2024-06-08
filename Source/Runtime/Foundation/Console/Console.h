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

    protected:
        virtual void InternalOutputString(const std::string& s, ConsoleTextColor color) = 0;
        virtual bool GetInternalReadyInputString(std::string& ret) = 0;
    public:
        virtual void InputPrefix() = 0;
        virtual void ProcessInputEvents() = 0;

    protected:
        const std::string PREFIX = ">>> ";


    public:
        static void Init();
        static void UnInit();
        static void OnOutputString(const std::string& s, ConsoleTextColor color);
        static bool GetReadyInputString(std::string& ret);

    private:
        static Console* CreatePlatformIndependentConsole();

    public:
        static CriticalSection ConsoleProtection;

    private:
        static Console* Instance_;
        static RunnableThread* InputThread_;
        static Runnable* InputRunnable_;

    };

}

