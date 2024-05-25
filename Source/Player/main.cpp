#include "Runtime/Application/Platform/Windows/WindowsApplication.h"

using namespace mikasa::Runtime::Application;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = false;
    param.LogPath = "Logs/Player.log";
    param.LogDir = "Logs";

    WindowsApplication player;
    player.Init(param);
    player.Run();
    player.UnInit();
    return 0;
}