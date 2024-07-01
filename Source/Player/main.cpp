#include "Runtime/Framework/Application/Platform/Windows/WindowsApplication.h"

using namespace mikasa::Runtime::Framework;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = false;
    param.WindowTitle = "mikasa player";
    param.LogPath = "Logs/Player.log";
    param.LogDir = "Logs";

    WindowsApplication player;
    Application::Param = param;
    player.Init(param);
    player.Run();
    player.UnInit();
    return 0;
}