
#include "RenderTarget.h"

using namespace mikasa::Runtime::Core;

RenderTarget::RenderTarget(const RenderTextureDesc& desc) : RenderTexture(desc)
{

}

void RenderTarget::InitRHIResource()
{
    RenderTexture::InitRHIResource();
}


