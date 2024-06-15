
#include "ScriptModule.h"

#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/Console/Console.h"
#include "Runtime/Core/Script/Python/PythonVM.h"

using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

ScriptVM* ScriptModule::VM_ = nullptr;

void ScriptModule::Init(const ApplicationInitParam& info)
{
    VM_ = new PythonVM();
    Logger::Info("ScriptModule Init ok.");
}

void ScriptModule::UnInit()
{
    MIKASA_ASSERT(VM_ != nullptr);
    delete VM_;
    VM_ = nullptr;
}

#if MIKASA_BUILDTYPE_DEBUG
void ScriptModule::ConsumeConsoleInput()
{
    MIKASA_ASSERT(VM_ != nullptr);
    std::string input;
    if (Console::GetReadyInputString(input))
    {
        if (input.length() <= 0)
        {
            return;
        }
        VM_->EvaluateString(input);
    }
}

void ScriptModule::DoString(const std::string& s)
{
    MIKASA_ASSERT(VM_ != nullptr);
    VM_->EvaluateString(s);
}

#endif