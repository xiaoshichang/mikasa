#pragma once
#include "Runtime/Core/Scene/Scene.h"
#include <string>

using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Module
{

    class SceneModule
    {
    public:
        static void Init();
        static void UnInit();
        static void Update();

    public:
        static void SyncLoadScene(const std::string& path);
        static Scene* Current;

    private:
        static void DoSyncLoadScene(const std::string& path);
        static void DestroyCurrentScene();

    private:
    };

}

