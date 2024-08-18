#pragma once
#include "../../Panel.h"
#include "Runtime/Core/Scene/Transform.h"
#include "Runtime/Core/Scene/Component/CameraCmpt.h"
#include <memory>

namespace mikasa::Runtime::Core
{
    class RenderTarget;
    class RenderViewFamily;
    class RenderView;
    class GameObject;
}

namespace mikasa::Editor
{
    struct SceneCamera
    {
        mikasa::Runtime::Core::Transform SceneCameraTransform;
        mikasa::Runtime::Core::Camera Camera;

        Matrix4x4f GetViewMatrix();
    };


    class ScenePanel : public Panel
    {
    public:
        ScenePanel();
        void Init() override;
        void InitSceneColorRT();
        void InitSceneCamera();
        void UnInit() override;

    protected:
        void HandleInput() override;
        void RenderContent() override;


    private:
        std::shared_ptr<mikasa::Runtime::Core::RenderViewFamily> BuildSceneViewFamily();
        std::shared_ptr<mikasa::Runtime::Core::RenderView> BuildSceneView();


    private:
        SceneCamera SceneCamera_;
        std::shared_ptr<mikasa::Runtime::Core::RenderTarget> SceneColorRT_;


    };
}

