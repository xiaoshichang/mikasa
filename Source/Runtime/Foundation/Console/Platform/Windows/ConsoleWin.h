#pragma once
#include "../../Console.h"
#include <windows.h>


namespace mikasa::Runtime::Foundation
{
    class ConsoleWin : public Console
    {
    public:
        ConsoleWin();
        ~ConsoleWin() override;

    public:
        static bool WINAPI ConsoleHandler(DWORD dwCtrlType);

    protected:
        void InternalOutputString(const std::string &s, ConsoleTextColor color) override;
        void DoOutput(const std::string &s, ConsoleTextColor color);

    public:
        void ProcessInputEvents() override;

        void InputPrefix() override;

    private:
        void ProcessKeyDown(KEY_EVENT_RECORD  keyEvent);
        void ClearInputPart();
        void ShowInputPart();

    private:
        static int ConvertColor(ConsoleTextColor color);

    private:
        HWND Internal_;
        HANDLE OutputHandle_;
        HANDLE InputHandle_;
        std::string Input_;
        COORD OutputCursor_;

    };

}
