#ifdef MIKASA_TARGET_PLATFORM_Window

#include "WindowsApplication.h"

using namespace mikasa::Runtime::Application;

void WindowsApplication::Init(const ApplicationInitParam& param)
{
    ApplicationBase::Init(param);
}

void WindowsApplication::UnInit()
{
    ApplicationBase::UnInit();
}

#endif