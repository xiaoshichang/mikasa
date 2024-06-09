#pragma once

#include <string>
#include "Runtime/Foundation/Foundation.h"

namespace mikasa::Runtime::Core
{
    struct ApplicationInitParam
    {
        ApplicationInitParam() = default;
        ApplicationInitParam(int argc, char** argv);

        bool EditorMode = false;
        int32 WindowWidth = 0;
        int32 WindowHeight = 0;
        int32 WindowOffsetX = 0;
        int32 WindowOffsetY = 0;
        bool WindowResizeable = false;

        std::string WindowTitle;
        std::string LogDir;
        std::string LogPath;
    };
}




