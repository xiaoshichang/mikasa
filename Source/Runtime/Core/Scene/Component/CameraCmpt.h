#pragma once
#include "Component.h"
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Render/Renderer/RenderViewInfo.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    enum ProjectionType
    {
        Orthographic,
        Perspective
    };

    class Camera
    {
    public:
        Camera(ProjectionType projectionType,
               float nearPlane,
               float farPlane,
               float fovInAngle,
               float viewWidthInPixel,
               float viewHeightInPixel);

        Matrix4x4f GetProjectionMatrix();

    private:
        ProjectionType ProjectionType_ = ProjectionType::Perspective;
        float NearPlane_;
        float FarPlane_;
        float FovInAngle_;
        float AspectRatio_;
        float ViewWidthInPixel_;
        float ViewHeightInPixel_;
        bool ProjectionMatrixDirty_ = true;
        Matrix4x4f ProjectionMatrix_ = Matrix4x4f::Identity();
    };


    class CameraCmpt : public Component
    {
    public:
        explicit CameraCmpt(GameObject* owner);
        ~CameraCmpt() override;
        Camera* GetCamera();
        Matrix4x4f GetViewMatrix();
        std::shared_ptr<RenderViewInfo> CreateRenderViewInfo();


    private:
        Camera* Camera_ = nullptr;
    };

}
