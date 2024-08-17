
#include "RenderView.h"
#include "Runtime/Core/Scene/Component/CameraCmpt.h"

using namespace mikasa::Runtime::Core;

/**
 * copy data from main thread camera to render thread view
 */
RenderView::RenderView(const RenderViewInitializer &initializer)
    : Camera(initializer.Camera)
{
    ConstantBufferPerViewData_.ViewMatrix = initializer.ViewMatrix;
    ConstantBufferPerViewData_.ProjectionMatrix =  initializer.ProjectionMatrix;
}

void RenderView::InitRHIResource()
{
    ConstantBufferPerView_ = std::make_shared<ConstantBuffer<ConstantBufferPerView>>(ConstantBufferPerViewData_);
}

ConstantBuffer<ConstantBufferPerView>* RenderView::GetConstantBufferPerView()
{
    return ConstantBufferPerView_.get();
}


