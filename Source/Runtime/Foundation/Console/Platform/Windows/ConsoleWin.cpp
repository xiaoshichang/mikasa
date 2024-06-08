#if MIKASA_TARGET_PLATFORM_Window

#include "../../../Foundation.h"
#include "ConsoleWin.h"

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
        Input_ = Input_ + c;
        Console::ConsoleProtection.Enter();
        int written;
        if (!WriteConsole(OutputHandle_, &c, 1, reinterpret_cast<LPDWORD>(&written), nullptr))
        {
            throw;
        }
        Console::ConsoleProtection.Exit();
    }
    else if (c == '\r')
    {
        auto log = PREFIX + Input_ + '\n';
        ReadyInputs_.push(Input_);

        Console::ConsoleProtection.Enter();
        DoOutput(log, ConsoleTextColor::LightGreen);
        ClearInputPart();
        Input_.clear();
        ShowInputPart();
        Console::ConsoleProtection.Exit();
    }
    else if (keyEvent.wVirtualKeyCode == VK_BACK)
    {
        if (Input_.length() <= 0)
        {
            return;
        }
        Input_ = Input_.substr(0, Input_.length() - 1);
        Console::ConsoleProtection.Enter();
        CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
        if (!GetConsoleScreenBufferInfo(OutputHandle_, &ScreenInfo))
        {
            throw;
        }

        auto current = ScreenInfo.dwCursorPosition;
        current.X -= 1;
        SetConsoleCursorPosition(OutputHandle_, current);

        DWORD cCharsWritten;
        if (!FillConsoleOutputCharacter(OutputHandle_,          // Handle to console screen buffer
                                        (TCHAR)' ',                 // Character to write to the buffer
                                        1,                   // Number of cells to write
                                        current,             // Coordinates of first cell
                                        &cCharsWritten)) // Receive number of characters written
        {
            throw;
        }
        MIKASA_ASSERT(cCharsWritten == 1);
        Console::ConsoleProtection.Exit();
    }
    else
    {
        // todo
    }
}


void ConsoleWin::ClearInputPart()
{
    CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
    if (!GetConsoleScreenBufferInfo(OutputHandle_, &ScreenInfo))
    {
        throw;
    }

    // clear input echo
    auto inputCount = PREFIX.length() + Input_.length();
    DWORD cCharsWritten;
    DWORD error;
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

#endif
