#if MIKASA_TARGET_PLATFORM_Window

#pragma once
#include <boost/lockfree/spsc_queue.hpp>
#include "../../Console.h"
#include <windows.h>


namespace mikasa::Runtime::Foundation
{
    class ConsoleWin : public Console
    {
    public:
        ConsoleWin();
        ~ConsoleWin() override;

    protected:
        void InternalOutputString(const std::string &s, ConsoleTextColor color) override;
        void DoOutput(const std::string &s, ConsoleTextColor color);
        bool GetInternalReadyInputString(std::string& ret) override;

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
        COORD OutputCursor_;

        /**
         * current input
         */
        std::string Input_;

        /**
         * ready inputs
         */
        boost::lockfree::spsc_queue<std::string> ReadyInputs_;
    };

}


#endif