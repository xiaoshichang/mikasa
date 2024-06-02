#pragma once

#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Framework
{
    class Application;
    class MainWindow
    {
    public:
        explicit MainWindow(Application* application);
        virtual ~MainWindow() = default;

    private:
        Application* Application_;

    public:
        static void Init(Application *application, const ApplicationInitParam& info);
        static void UnInit();
        static MainWindow* CreatePlatformIndependentMainWindow(Application *application, const ApplicationInitParam& info);


    private:
        static MainWindow* Instance_;
    };

}

