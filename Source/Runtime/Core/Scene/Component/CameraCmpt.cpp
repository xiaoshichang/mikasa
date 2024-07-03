
#include "CameraCmpt.h"
#include "../GameObject.h"

#include "Runtime/Framework/Application/Application.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Framework;

Camera::Camera(ProjectionType projectionType,
               float nearPlane,
               float farPlane,
               float fovInAngle,
               float viewWidthInPixel,
               float viewHeightInPixel)
       : ProjectionType_(projectionType)
       , NearPlane_(nearPlane)
       , FarPlane_(farPlane)
       , FovInAngle_(fovInAngle)
       , ViewHeightInPixel_(viewHeightInPixel)
       , ViewWidthInPixel_(viewWidthInPixel)
{
}

Matrix4x4f Camera::GetProjectionMatrix()
{
    if (ProjectionMatrixDirty_)
    {
        if (ProjectionType_ == ProjectionType::Perspective)
        {
            auto fovInRadius = FovInAngle_ / 360 * PI;
            auto aspectRatio = ViewWidthInPixel_ / ViewHeightInPixel_;
            ProjectionMatrix_ = MatrixPerspectiveFovLH01(fovInRadius, aspectRatio, NearPlane_, FarPlane_);
        }
        else if (ProjectionType_ == ProjectionType::Orthographic)
        {
            ProjectionMatrix_ = MatrixOrthographicLH01(ViewWidthInPixel_, ViewHeightInPixel_, NearPlane_, FarPlane_);
        }
        else
        {
            throw;
        }
        ProjectionMatrixDirty_ = false;
    }
    return ProjectionMatrix_;
}

ProjectionType Camera::GetProjectionType()
{
    return ProjectionType_;
}

void Camera::SetProjectionType(ProjectionType pt)
{
    ProjectionType_ = pt;
    ProjectionMatrixDirty_ = true;
}

float Camera::GetNearPlane() const
{
    return NearPlane_;
}

void Camera::SetNearPlane(float value)
{
    NearPlane_ = value;
    ProjectionMatrixDirty_ = true;
}

float Camera::GetFarPlane() const
{
    return FarPlane_;
}

void Camera::SetFarPlane(float value)
{
    FarPlane_ = value;
    ProjectionMatrixDirty_ = true;
}

float Camera::GetFovInAngle() const
{
    return FovInAngle_;
}

void Camera::SetFovInAngle(float value)
{
    FovInAngle_ = value;
    ProjectionMatrixDirty_ = true;
}

float Camera::GetViewWidthInPixel() const
{
    return ViewWidthInPixel_;
}

void Camera::SetViewWidthInPixel(float value)
{
    ViewWidthInPixel_ = value;
    ProjectionMatrixDirty_ = true;
}

float Camera::GetViewHeightInPixel() const
{
    return ViewHeightInPixel_;
}

void Camera::SetViewHeightInPixel(float value)
{
    ViewHeightInPixel_ = value;
    ProjectionMatrixDirty_ = true;
}


CameraCmpt::CameraCmpt(GameObject *owner) : Component(owner)
{
    auto projType = ProjectionType::Perspective;
    auto nearPlane = 0.1f;
    auto farPlane = 1000.0f;
    auto fovInAngle = 45.0f;
    auto viewWidthInPixel = (float)Application::Param.WindowWidth;
    auto viewHeightInPixel = (float)Application::Param.WindowHeight;

    Camera_ = new Camera(projType, nearPlane, farPlane, fovInAngle, viewWidthInPixel, viewHeightInPixel);
}

CameraCmpt::~CameraCmpt()
{
    delete Camera_;
    Camera_ = nullptr;
}

Camera *CameraCmpt::GetCamera()
{
    return Camera_;
}

Matrix4x4f CameraCmpt::GetViewMatrix()
{
    auto& transform = Owner_->GetTransform();
    auto eye = transform.GetPosition();
    auto focus = eye + transform.Forward();
    auto up = transform.Up();
    auto viewMatrix = MatrixLookAtLH(eye, Vector3f (0, 0, 0), up);
    return viewMatrix;
}