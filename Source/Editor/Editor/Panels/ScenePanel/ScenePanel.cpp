
#include "ScenePanel.h"
#include "Runtime/Framework/Application/Application.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/RenderTarget.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/RenderDevice/RHI/DX11/RHIShaderResourceViewDX11.h"
#include "Runtime/Core/Render/Renderer/SimpleForwardRenderer/SimpleForwardRenderer.h"
#include "Runtime/Module/SceneModule/SceneModule.h"

#include <memory>

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;


Matrix4x4f SceneCamera::GetViewMatrix()
{
    auto eye = SceneCameraTransform.GetPosition();
    auto focus = eye + SceneCameraTransform.Forward();
    auto up = SceneCameraTransform.Up();
    auto viewMatrix = MatrixLookAtLH(eye, focus, up);
    return viewMatrix;
}

ScenePanel::ScenePanel() : Panel("Scene")
{

}


void ScenePanel::Init()
{
    InitSceneColorRT();
    InitSceneCamera();
}

void ScenePanel::InitSceneColorRT()
{
    RenderTextureDesc desc{};
    desc.Format = PixelFormat::PF_R8G8B8A8_UNorm;

    if (Application::Param.EditorMode)
    {
        desc.Width = 1024;
        desc.Height = 768;
    }
    else
    {
        desc.Width = Application::Param.WindowWidth;
        desc.Height = Application::Param.WindowHeight;
    }

    desc.Flag |= RHITextureCreateFlag::TCF_AsRenderTarget;
    desc.Flag |= RHITextureCreateFlag::TCF_AsShaderResource;

    SceneColorRT_ = std::make_shared<RenderTarget>(desc);
    auto rt = SceneColorRT_;
    auto lambda = [=] ()
    {
        rt->InitRHIResource();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void ScenePanel::InitSceneCamera()
{
    SceneCamera_.SceneCameraTransform.SetPosition(Vector3f(10.0f, 10, 10));
    SceneCamera_.SceneCameraTransform.LookAt(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
}

void ScenePanel::UnInit()
{
    SceneColorRT_.reset();
}

void ScenePanel::HandleInput()
{
    if (ImGui::IsWindowFocused())
    {
        if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
        {
            if (ImGui::IsKeyDown(ImGuiKey_W))
            {
                Logger::Info("forward");
            }
            else if (ImGui::IsKeyDown(ImGuiKey_S))
            {

            }
            else if (ImGui::IsKeyDown(ImGuiKey_A))
            {

            }
            else if (ImGui::IsKeyDown(ImGuiKey_D))
            {

            }
        }
    }
}

void ScenePanel::RenderContent()
{
    auto scene = SceneModule::Current->GetRenderScene();
    auto viewFamily = BuildSceneViewFamily();
    auto renderer = new SimpleForwardRenderer(scene, viewFamily);
    auto lambda = [renderer]()
    {
        renderer->Render();
        delete renderer;
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);

    auto srv = (RHIShaderResourceViewDX11*)(SceneColorRT_->AsShaderResourceView());
    auto texture = (ImTextureID)srv->GetInternal();
    auto width = 1024 * 0.6;
    auto height = 768 * 0.6;

    ImGui::Text("---");
    ImGui::Image(texture, ImVec2((float)width, (float)height), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));
    ImGui::Text("---");
}

std::shared_ptr<RenderViewFamily> ScenePanel::BuildSceneViewFamily()
{
    RenderViewFamilyInitializer rvfi;
    rvfi.RenderTarget = SceneColorRT_;
    rvfi.ClearColor = Vector4f(0.2, 0.3, 0.4, 1.0);
    auto view = BuildSceneView();
    rvfi.Views.push_back(view);

    // only support single scene camera
    MIKASA_ASSERT(rvfi.Views.size() == 1);

    return std::make_shared<RenderViewFamily>(rvfi);
}

std::shared_ptr<mikasa::Runtime::Core::RenderView> ScenePanel::BuildSceneView()
{
    RenderViewInitializer initializer;
    initializer.Camera = SceneCamera_.Camera;
    initializer.ProjectionMatrix = SceneCamera_.Camera.GetProjectionMatrix();
    initializer.ViewMatrix = SceneCamera_.GetViewMatrix();
    return std::make_shared<RenderView>(initializer);
}







