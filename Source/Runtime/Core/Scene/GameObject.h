#pragma once
#include "Runtime/Foundation/Foundation.h"
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

    private:
        Scene* Scene_ = nullptr;
        std::string Name_;

    ///////////////////////////// transform //////////////////////////////////
    public:
        Vector3f GetPosition() const;
        void SetPosition(Vector3f position);
        Vector3f GetScale() const;
        void SetScale(Vector3f scale);
        Quaternion GetRotation() const;
        void SetRotation(Quaternion quaternion);
        Matrix4x4f GetWorldMatrix();

    private:
        Vector3f Position_ = Vector3f (0, 0, 0);
        Vector3f Scale_ = Vector3f (1, 1, 1);
        Quaternion Rotation_ = Quaternion::Identity();
        bool WorldMatrixDirty_ = true;
        Matrix4x4f WorldMatrix_ = Matrix4x4f::Identity();

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


