
#include "WindowsPlayer.h"
#include "Runtime/Module/SceneModule/SceneModule.h"

using namespace mikasa::Player;
using namespace mikasa::Runtime::Module;

void WindowsPlayer::Init(const ApplicationInitParam &info)
{
    WindowsApplication::Init(info);
    SceneModule::SyncLoadScene("");
}
