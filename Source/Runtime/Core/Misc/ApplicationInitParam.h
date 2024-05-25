#pragma once

#include <string>

namespace mikasa
{
    namespace Runtime
    {
        namespace Core
        {
            struct ApplicationInitParam
            {
                ApplicationInitParam(int argc, char** argv);

                bool EditorMode;
                int WindowWidth;
                int WindowHeight;
                int WindowOffsetX;
                int WindowOffsetY;
                std::wstring WindowTitle;
                std::wstring LogDir;
                std::wstring LogPath;
            };
        }
    }
}


