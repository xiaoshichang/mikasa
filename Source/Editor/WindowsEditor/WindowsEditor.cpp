
#include "WindowsEditor.h"
#include "Runtime/Module/SceneModule/SceneModule.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Module;

void WindowsEditor::Init(const ApplicationInitParam &info)
{
    WindowsApplication::Init(info);
    SceneModule::SyncLoadScene("");
}
