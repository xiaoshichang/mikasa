#include "Runtime/Application/Platform/Windows/WindowsApplication.h"

using namespace mikasa::Runtime::Application;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = false;

    WindowsApplication player;
    player.Init(param);
    player.Run();
    player.UnInit();
    return 0;
}