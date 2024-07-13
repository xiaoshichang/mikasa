#include "Runtime/Framework/Application/Platform/Windows/WindowsApplication.h"
#include "Editor/WindowsEditor/WindowsEditor.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Framework;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = true;
    param.WindowWidth = 1580;
    param.WindowHeight = 1200;

    param.WindowTitle = "mikasa editor";
    param.LogDir = "Logs";
    param.LogPath = "Logs/Editor.log";



    WindowsEditor editor;
    Application::Param = param;
    editor.Init(param);
    editor.Run();
    editor.UnInit();
    return 0;
}