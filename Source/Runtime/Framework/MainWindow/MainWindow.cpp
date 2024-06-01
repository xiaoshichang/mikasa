
#include "MainWindow.h"
#if MIKASA_TARGET_PLATFORM_Window
#include "Platform/Windows/MainWindowWin.h"
#else
#error
#endif


using namespace mikasa::Runtime::Framework;

MainWindow* MainWindow::MainWindow_ = nullptr;

MainWindow::MainWindow(Application *application)
    : Application_(application)
{

}


void MainWindow::Init(Application *application, const ApplicationInitParam& info)
{
    MIKASA_ASSERT(MainWindow_ == nullptr);
    MainWindow_ = CreatePlatformIndependentMainWindow(application, info);
}

void MainWindow::UnInit()
{
    MIKASA_ASSERT(MainWindow_ != nullptr);
    delete MainWindow_;
    MainWindow_ = nullptr;
}

MainWindow *MainWindow::CreatePlatformIndependentMainWindow(Application *application, const ApplicationInitParam &info)
{
#if MIKASA_TARGET_PLATFORM_Window
    return new MainWindowWin(application, info);
#else
    #error
#endif
}

