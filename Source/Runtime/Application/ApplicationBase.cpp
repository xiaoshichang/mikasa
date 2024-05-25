#include "ApplicationBase.h"
#include "Runtime/Module/Log/LogModule.h"

using namespace mikasa::Runtime::Application;
using namespace mikasa::Runtime::Module;

void ApplicationBase::Init(const ApplicationInitParam& info)
{
    LogModule::Init(info);
}

void ApplicationBase::Run()
{
    while (!IsApplicationQuit_)
    {
    }
}

void ApplicationBase::UnInit(){

}

void ApplicationBase::TryQuit()
{
    IsApplicationQuit_ = true;
}
