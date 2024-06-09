#pragma once

#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"
#include "Runtime/Module/RenderModule/RenderModule.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Module;

namespace mikasa::Runtime::Framework
{
    class Application;
    class MainWindow
    {
    public:
        explicit MainWindow(Application* application);
        virtual ~MainWindow() = default;
        virtual WindowHandler GetInternalWindowHandler() = 0;

    private:
        Application* Application_;

    public:
        static void Init(Application *application, const ApplicationInitParam& info);
        static void UnInit();
        static MainWindow* CreatePlatformIndependentMainWindow(Application *application, const ApplicationInitParam& info);
        static WindowHandler GetWindowHandler();

    private:
        static MainWindow* Instance_;
    };

}

