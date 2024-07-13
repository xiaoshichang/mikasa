#pragma once
#include "../Panel.h"

namespace mikasa::Editor
{
    class MainMenuBar
    {
    public:
        MainMenuBar();
        void Render();

    private:
        void RenderView();
    };
}

