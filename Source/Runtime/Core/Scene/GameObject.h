#pragma once
#include "Runtime/Foundation/Foundation.h"
#include "Transform.h"
#include "Component/StaticMeshRenderCmpt.h"
#include "Component/CameraCmpt.h"
#include "Component/LightCmpt.h"

#include <string>
#include <vector>

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class Scene;
    class GameObject
    {
    private:
        explicit GameObject(Scene* scene, std::string name);
        ~GameObject();

    public:
        friend class Scene;
        Scene* GetScene() const;
        const std::string& GetName() const;
        Transform& GetTransform();

    private:
        Scene* Scene_ = nullptr;
        std::string Name_;
        Transform Transform_;

    ///////////////////////////// StaticMeshRenderCmpt ////////////////////////////
    public:
        void InitStaticMeshRenderCmpt();
        void UnInitStaticMeshRenderCmpt();
        StaticMeshRenderCmpt* GetStaticMeshRenderCmpt();
    private:
        StaticMeshRenderCmpt* StaticMeshRenderCmpt_ = nullptr;


    ///////////////////////////// CameraCmpt ////////////////////////////
    public:
        void InitCameraCmpt();
        void UnInitCameraCmpt();
        CameraCmpt* GetCameraCmpt();
    private:
        CameraCmpt* CameraCmpt_ = nullptr;

    ///////////////////////////// LightCmpt ////////////////////////////

    public:
        void InitLightCmpt();
        void UnInitLightCmpt();
        LightCmpt* GetLightCmpt();
    private:
        LightCmpt* LightCmpt_ = nullptr;

    };
}


