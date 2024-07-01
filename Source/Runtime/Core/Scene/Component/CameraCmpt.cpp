
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
       , AspectRatio_(viewWidthInPixel / viewHeightInPixel)
{
}

Matrix4x4f Camera::GetProjectionMatrix()
{
    if (ProjectionMatrixDirty_)
    {
        if (ProjectionType_ == ProjectionType::Perspective)
        {
            auto fovInRadius = FovInAngle_ / 360 * PI;
            ProjectionMatrix_ = MatrixPerspectiveFovLH01(fovInRadius, AspectRatio_, NearPlane_, FarPlane_);
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
    auto viewMatrix = MatrixLookAtLH(eye, focus, up);
    return viewMatrix;
}

std::shared_ptr<RenderViewInfo> CameraCmpt::CreateRenderViewInfo()
{
    MIKASA_ASSERT(Camera_ != nullptr);
    std::shared_ptr<RenderViewInfo> rvi = std::make_shared<RenderViewInfo>();
    rvi->ViewMatrix = GetViewMatrix();
    rvi->ProjectionMatrix = Camera_->GetProjectionMatrix();
    rvi->ClearColor = Vector4f(0.2, 0.3, 0.4, 1.0);
    return rvi;
}



