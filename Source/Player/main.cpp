#include "WindowsPlayer/WindowsPlayer.h"

using namespace mikasa::Runtime::Framework;
using namespace mikasa::Player;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = false;
    param.WindowTitle = "mikasa player";
    param.LogPath = "Logs/Player.log";
    param.LogDir = "Logs";

    WindowsPlayer player;
    Application::Param = param;
    player.Init(param);
    player.Run();
    player.UnInit();
    return 0;
}