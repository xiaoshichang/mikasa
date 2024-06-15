#if MIKASA_TARGET_PLATFORM_Window

#include "../../../Foundation.h"
#include "ConsoleWin.h"
#include <cmath>
#include <algorithm>

using namespace mikasa::Runtime::Foundation;

ConsoleWin::ConsoleWin()
    : ReadyInputs_(10)
{
    if (AllocConsole() == 0)
    {
        throw;
    }
    Internal_ = GetConsoleWindow();

    SetWindowPos(Internal_, 0, 1024 + 1, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetConsoleTitleW(L"Mikasa Console");

    // https://stackoverflow.com/questions/53256389/c-winapi-getconsolescreenbufferinfo-always-fails-by-invalid-handle-returns
    OutputHandle_ = CreateFile("CONOUT$",GENERIC_WRITE|GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (OutputHandle_ == INVALID_HANDLE_VALUE)
    {
        throw;
    }
    InputHandle_ = CreateFile("CONIN$",GENERIC_WRITE|GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (InputHandle_ == INVALID_HANDLE_VALUE)
    {
        throw;
    }

    // https://stackoverflow.com/questions/37069599/cant-read-mouse-event-use-readconsoleinput-in-c
    //if (! SetConsoleMode(InputHandle_, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT) )

    CONSOLE_SCREEN_BUFFER_INFO ScreenInfo{};
    if (!GetConsoleScreenBufferInfo(OutputHandle_, &ScreenInfo))
    {
        throw;
    }
    OutputCursor_ = ScreenInfo.dwCursorPosition;
}

ConsoleWin::~ConsoleWin()
{
    FreeConsole();
    Internal_ = nullptr;
    OutputHandle_ = nullptr;
    InputHandle_ = nullptr;
}

int ConsoleWin::ConvertColor(ConsoleTextColor color)
{
    if (color == ConsoleTextColor::White)
    {
        return 15;
    }
    else if (color == ConsoleTextColor::Yellow)
    {
        return 14;
    }
    else if (color == ConsoleTextColor::LightGreen)
    {
        return 10;
    }
    else if (color == ConsoleTextColor::LightRed)
    {
        return 12;
    }
    else
    {
        MIKASA_ASSERT(false);
        return 15;
    }
}

void ConsoleWin::InternalOutputString(const std::string &s, ConsoleTextColor color)
{
    ConsoleProtection.Enter();
    DoOutput(s, color);
    ConsoleProtection.Exit();
}

void ConsoleWin::ProcessInputEvents()
{
    DWORD  eventCount = 0;
    INPUT_RECORD irInBuf[128];

    WaitForSingleObject(InputHandle_, 1);

    if (!GetNumberOfConsoleInputEvents(InputHandle_, &eventCount))
    {
        return;
    }
    if (eventCount <= 0)
    {
        return;
    }
    if (!ReadConsoleInput(InputHandle_, irInBuf, 128, &eventCount))
    {
        throw;
    }
    for(int i = 0; i < eventCount; i++)
    {
        switch(irInBuf[i].EventType)
        {
            case KEY_EVENT: // keyboard input
            {
                ProcessKeyDown(irInBuf[i].Event.KeyEvent);
                break;
            }
            case MOUSE_EVENT: // mouse input
            {
                break;
            }
            case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
            {
                break;
            }
            case FOCUS_EVENT:  // disregard focus events
            {
                break;
            }
            case MENU_EVENT:   // disregard menu events
            {
                break;
            }
            default:
                throw;
        }
    }
}

void ConsoleWin::ProcessKeyDown(KEY_EVENT_RECORD  keyEvent)
{
    if (!keyEvent.bKeyDown)
    {
        return;
    }

    auto c = keyEvent.uChar.AsciiChar;
    std::string digits = ".+-*/[]{}=_)(*&^%$#@!~?><\";:'";
    if (std::isalnum(c) || c == ' ' || digits.find(c) != std::string::npos)
    {
        ProcessKeyDown_NormalChar(c);
    }
    else if (c == '\r')
    {
        ProcessKeyDown_Newline();
    }
    else if (keyEvent.wVirtualKeyCode == VK_BACK)
    {
        ProcessKeyDown_Backspace();
    }
    else if (keyEvent.wVirtualKeyCode == VK_LEFT)
    {
        ProcessKeyDown_Left();
    }
    else if (keyEvent.wVirtualKeyCode == VK_RIGHT)
    {
        ProcessKeyDown_Right();
    }
    else if (keyEvent.wVirtualKeyCode == VK_UP)
    {
        ProcessKeyDown_Up();
    }
    else if (keyEvent.wVirtualKeyCode == VK_DOWN)
    {
        ProcessKeyDown_Down();
    }
    else
    {
        // todo
    }
}

void ConsoleWin::ProcessKeyDown_NormalChar(char c)
{
    Console::ConsoleProtection.Enter();
    ClearInputPart();
    Input_.insert(Input_.end() + CursorBackOffset_, c);
    ShowInputPart();
    Console::ConsoleProtection.Exit();
}

void ConsoleWin::ProcessKeyDown_Newline()
{
    auto log = PREFIX + Input_ + '\n';
    ReadyInputs_.push(Input_);

    Console::ConsoleProtection.Enter();
    DoOutput(log, ConsoleTextColor::LightGreen);
    ClearInputPart();
    AppendHistory(Input_);
    Input_.clear();
    CursorBackOffset_ = 0;
    InputHistorySelected_ = -1;
    ShowInputPart();

    Console::ConsoleProtection.Exit();
}

void ConsoleWin::ProcessKeyDown_Backspace()
{
    if (Input_.length() + CursorBackOffset_ <= 0)
    {
        return;
    }

    Console::ConsoleProtection.Enter();
    ClearInputPart();

    Input_.erase(Input_.end() - 1 + CursorBackOffset_);

    auto minValue = -((int)Input_.size());
    if (CursorBackOffset_ > 0)
    {
        CursorBackOffset_ = 0;
    }
    else if (CursorBackOffset_ < minValue)
    {
        CursorBackOffset_ = minValue;
    }

    ShowInputPart();
    Console::ConsoleProtection.Exit();
}

void ConsoleWin::ProcessKeyDown_Left()
{
    Console::ConsoleProtection.Enter();
    MoveBackOffset(true);
    Console::ConsoleProtection.Exit();
}

void ConsoleWin::ProcessKeyDown_Right()
{
    Console::ConsoleProtection.Enter();
    MoveBackOffset(false);
    Console::ConsoleProtection.Exit();
}

void ConsoleWin::ProcessKeyDown_Up()
{
    if (InputHistory_.empty())
    {
        return;
    }

    Console::ConsoleProtection.Enter();
    ClearInputPart();

    InputHistorySelected_ += 1;
    if (InputHistorySelected_ >= InputHistory_.size())
    {
        InputHistorySelected_ = (int(InputHistory_.size())) - 1;
    }
    Input_ = InputHistory_[InputHistorySelected_];
    CursorBackOffset_ = 0;

    ShowInputPart();
    Console::ConsoleProtection.Exit();
}

void ConsoleWin::ProcessKeyDown_Down()
{
    if (InputHistory_.empty())
    {
        return;
    }

    Console::ConsoleProtection.Enter();
    ClearInputPart();

    InputHistorySelected_ -= 1;
    if (InputHistorySelected_ < 0)
    {
        InputHistorySelected_ = -1;
        Input_ = "";
    }
    else
    {
        Input_ = InputHistory_[InputHistorySelected_];
    }
    CursorBackOffset_ = 0;

    ShowInputPart();
    Console::ConsoleProtection.Exit();
}



void ConsoleWin::ClearInputPart()
{
    // clear input echo
    auto inputCount = PREFIX.length() + Input_.length();
    DWORD cCharsWritten;
    if (!FillConsoleOutputCharacter(OutputHandle_,          // Handle to console screen buffer
                                    (TCHAR)' ',                 // Character to write to the buffer
                                    inputCount,                   // Number of cells to write
                                    OutputCursor_,             // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        throw;
    }
    MIKASA_ASSERT(cCharsWritten == inputCount);

    // set cursor to last output position
    SetConsoleCursorPosition(OutputHandle_, OutputCursor_);
}

void ConsoleWin::InputPrefix()
{
    SetConsoleTextAttribute(OutputHandle_, ConvertColor(ConsoleTextColor::LightGreen));
    DWORD written;
    if (!WriteConsoleOutputCharacter(OutputHandle_, PREFIX.c_str(), PREFIX.length(), OutputCursor_, &written))
    {
        throw;
    }
}

void ConsoleWin::ShowInputPart()
{
    SetConsoleTextAttribute(OutputHandle_, ConvertColor(ConsoleTextColor::LightGreen));
    DWORD written;
    if (!WriteConsole(OutputHandle_, PREFIX.c_str(), PREFIX.length(), &written, nullptr))
    {
        throw;
    }
    MIKASA_ASSERT(written == PREFIX.length());
    if (Input_.length() > 0)
    {
        if (!WriteConsole(OutputHandle_, Input_.c_str(), Input_.length(), &written, nullptr))
        {
            throw;
        }
        MIKASA_ASSERT(written == Input_.length());
    }

    MoveCursor(CursorBackOffset_);

}

void ConsoleWin::DoOutput(const std::string &s, ConsoleTextColor color)
{
    // clear input
    ClearInputPart();

    // output
    DWORD written;
    SetConsoleTextAttribute(OutputHandle_, ConvertColor(color));
    if(!WriteConsole(OutputHandle_, s.c_str(), s.length(), &written, nullptr))
    {
        throw;
    }
    MIKASA_ASSERT(written == s.length());

    // record new output position
    CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
    if (!GetConsoleScreenBufferInfo(OutputHandle_, &ScreenInfo))
    {
        throw;
    }
    OutputCursor_ = ScreenInfo.dwCursorPosition;

    // write input echo again
    ShowInputPart();
}

bool ConsoleWin::GetInternalReadyInputString(std::string& ret)
{
    if (ReadyInputs_.pop(ret))
    {
        return true;
    }
    return false;
}

void ConsoleWin::MoveCursor(int offset)
{
    CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
    if (!GetConsoleScreenBufferInfo(OutputHandle_, &ScreenInfo))
    {
        throw;
    }
    auto current = ScreenInfo.dwCursorPosition;
    current.X += offset;
    SetConsoleCursorPosition(OutputHandle_, current);
}

void ConsoleWin::MoveBackOffset(bool backward)
{
    auto offset = (backward ? -1 : 1);
    CursorBackOffset_ += offset;
    MoveCursor(offset);

    auto minValue = -((int)Input_.size());
    if (CursorBackOffset_ > 0)
    {
        CursorBackOffset_ = 0;
        MoveCursor(-offset);
    }
    else if (CursorBackOffset_ < minValue)
    {
        CursorBackOffset_ = minValue;
        MoveCursor(-offset);
    }
}

void ConsoleWin::AppendHistory(const std::string& input)
{
    InputHistory_.insert(InputHistory_.begin(), input);
    if (InputHistory_.size() > 20)
    {
        auto end = InputHistory_.end();
        std::advance(end, -1);
        InputHistory_.erase(end);
    }
}



#endif
