#include "Runtime/Application/Platform/Windows/WindowsApplication.h"

using namespace mikasa::Runtime::Application;

int main(int argc, char** argv)
{
    ApplicationInitParam param(argc, argv);
    param.EditorMode = true;

    WindowsApplication editor;
    editor.Init(param);
    editor.Run();
    editor.UnInit();
    return 0;
}