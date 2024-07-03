
#include "RenderView.h"
#include "Runtime/Core/Scene/Component/CameraCmpt.h"

using namespace mikasa::Runtime::Core;

/**
 * copy data from main thread camera to render thread view
 */
RenderView::RenderView(const RenderViewInitializer &initializer)
    : Camera(*(initializer.CameraCmpt)->GetCamera())
{
    ConstantBufferPerViewData_.ViewMatrix = initializer.CameraCmpt->GetViewMatrix();
    ConstantBufferPerViewData_.ProjectionMatrix =  Camera.GetProjectionMatrix();
}

void RenderView::InitRHIResource()
{
    ConstantBufferPerView_ = std::make_shared<ConstantBuffer<ConstantBufferPerView>>(ConstantBufferPerViewData_);
}

ConstantBuffer<ConstantBufferPerView>* RenderView::GetConstantBufferPerView()
{
    return ConstantBufferPerView_.get();
}


