#pragma once

#include <string>
#include "Runtime/Foundation/Foundation.h"

namespace mikasa
{
    namespace Runtime
    {
        namespace Core
        {
            struct ApplicationInitParam
            {
                ApplicationInitParam(int argc, char** argv);

                bool EditorMode = false;
                int32 WindowWidth = 0;
                int32 WindowHeight = 0;
                int32 WindowOffsetX = 0;
                int32 WindowOffsetY = 0;

                std::string WindowTitle;
                std::string LogDir;
                std::string LogPath;
            };
        }
    }
}


