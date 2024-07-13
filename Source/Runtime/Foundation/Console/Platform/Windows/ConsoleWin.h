#if MIKASA_TARGET_PLATFORM_Window

#pragma once
#include <boost/lockfree/spsc_queue.hpp>
#include "../../Console.h"
#include <windows.h>


namespace mikasa::Runtime::Foundation
{
    struct ConsoleWinCreateInfo
    {
        int OffsetX;
        int OffsetY;
    };

    class ConsoleWin : public Console
    {
    public:
        ConsoleWin();
        ~ConsoleWin() override;

    protected:
        void OutputString(const std::string &s, ConsoleTextColor color) override;
        void DoOutput(const std::string &s, ConsoleTextColor color);
        bool GetReadyInputString(std::string& ret) override;

    public:
        void ProcessInputEvents() override;
        void InputPrefix() override;
        void SetOffset(int x, int y) override;

    private:
        void ProcessKeyDown(KEY_EVENT_RECORD  keyEvent);
        void ProcessKeyDown_NormalChar(char c);
        void ProcessKeyDown_Newline();
        void ProcessKeyDown_Backspace();
        void ProcessKeyDown_Left();
        void ProcessKeyDown_Right();
        void ProcessKeyDown_Up();
        void ProcessKeyDown_Down();

        void ClearInputPart();
        void ShowInputPart();
        void MoveCursor(int offset);
        void MoveBackOffset(bool backward);
        void AppendHistory(const std::string& input);

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

        int CursorBackOffset_ = 0;

        std::vector<std::string> InputHistory_;
        int InputHistorySelected_ = -1;
    };

}


#endif