#pragma once
#include <string>
#include "imgui.h"

namespace mikasa::Editor
{
    class Panel
    {
    public:
        explicit Panel(std::string  windowName);
        virtual ~Panel() = default;

    public:
        virtual void Init() = 0;
        virtual void UnInit() = 0;
        void RenderWindow();

    protected:
        virtual void RenderContent() = 0;

    public:
        void Show() { IsShow_ = true; }
        void Hide() { IsShow_ = false;}

    protected:
        std::string WindowName_;
        bool IsShow_ = true;
        int WindowFlag_ = ImGuiWindowFlags_NoCollapse;
    };
}

