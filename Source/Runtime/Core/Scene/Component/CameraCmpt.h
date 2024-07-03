#pragma once
#include "Component.h"
#include "Runtime/Foundation/Foundation.h"

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
        ProjectionType GetProjectionType();
        void SetProjectionType(ProjectionType pt);
        float GetNearPlane() const;
        void SetNearPlane(float value);
        float GetFarPlane() const;
        void SetFarPlane(float value);
        float GetFovInAngle() const;
        void SetFovInAngle(float value);
        float GetAspectRatio();
        float GetViewWidthInPixel() const;
        void SetViewWidthInPixel(float value);
        float GetViewHeightInPixel() const;
        void SetViewHeightInPixel(float value);


    private:
        ProjectionType ProjectionType_ = ProjectionType::Perspective;
        float NearPlane_;
        float FarPlane_;
        float FovInAngle_;
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


    private:
        Camera* Camera_ = nullptr;
    };

}
