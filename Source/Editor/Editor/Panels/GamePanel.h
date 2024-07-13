#pragma once
#include "../Panel.h"

namespace mikasa::Editor
{
    class GamePanel : public Panel
    {
    public:
        GamePanel();
        void Init() override;
        void UnInit() override;

    protected:
        void RenderContent() override;

    };
}

