#include "Runtime/Framework/Application/Platform/Windows/WindowsApplication.h"

using namespace mikasa::Runtime::Framework;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = true;
    param.WindowTitle = "mikasa editor";
    param.LogDir = "Logs";
    param.LogPath = "Logs/Editor.log";

    WindowsApplication editor;
    editor.Init(param);
    editor.Run();
    editor.UnInit();
    return 0;
}