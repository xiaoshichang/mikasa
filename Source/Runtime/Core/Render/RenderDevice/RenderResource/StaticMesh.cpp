
#include "StaticMesh.h"
#include "../RenderDevice.h"
#include "../RHI/RHIBoundShaderState.h"


using namespace mikasa::Runtime::Core;

static Vector3f g_PositionData[8] =
        {
                Vector3f(-1.0f, -1.0f, -1.0f),
                Vector3f(-1.0f,  1.0f, -1.0f),
                Vector3f(1.0f,  1.0f, -1.0f),
                Vector3f(1.0f, -1.0f, -1.0f),
                Vector3f(-1.0f, -1.0f,  1.0f),
                Vector3f(-1.0f,  1.0f,  1.0f),
                Vector3f(1.0f,  1.0f,  1.0f),
                Vector3f(1.0f, -1.0f,  1.0f)

        };

static Vector3f g_ColorData[8] =
        {
                Vector3f(0.0f, 0.0f, 0.0f), // 0
                Vector3f(0.0f, 1.0f, 0.0f), // 1
                Vector3f(1.0f, 1.0f, 0.0f), // 2
                Vector3f(1.0f, 0.0f, 0.0f), // 3
                Vector3f(0.0f, 0.0f, 1.0f), // 4
                Vector3f(0.0f, 1.0f, 1.0f), // 5
                Vector3f(1.0f, 1.0f, 1.0f), // 6
                Vector3f(1.0f, 0.0f, 1.0f)  // 7
        };

static unsigned short g_Indicies[36] =
        {
                0, 1, 2, 0, 2, 3,
                4, 6, 5, 4, 7, 6,
                4, 5, 1, 4, 1, 0,
                3, 2, 6, 3, 6, 7,
                1, 5, 6, 1, 6, 2,
                4, 0, 3, 4, 3, 7
        };

StaticMesh::StaticMesh(const std::string& asset)
{
    auto positionData = new Vector3f[8];
    memcpy_s(positionData, sizeof(g_PositionData), g_PositionData, sizeof(g_PositionData));
    PositionCmpt_ = std::make_shared<VertexStreamCmpt>((uint8*)positionData, (uint32)sizeof(g_PositionData), VertexElementType::VET_Float3);


    auto colorData = new Vector3f [8];
    memcpy_s(colorData, sizeof(g_ColorData), g_ColorData, sizeof(g_ColorData));
    ColorCmpt_ = std::make_shared<VertexStreamCmpt>((uint8*)colorData, (uint32)sizeof(g_ColorData),  VertexElementType::VET_Float3);

    auto lambda = [this]()
    {
        InitRHIResource();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

StaticMesh::~StaticMesh()
{
    PositionCmpt_.reset();
    NormalCmpt_.reset();
    ColorCmpt_.reset();
    ShaderState_.reset();
}

void StaticMesh::InitRHIResource()
{
    if (PositionCmpt_ != nullptr)
    {
        PositionCmpt_->InitRHIResource();
    }
    if (NormalCmpt_ != nullptr)
    {
        NormalCmpt_->InitRHIResource();
    }
    if (ColorCmpt_ != nullptr)
    {
        ColorCmpt_->InitRHIResource();
    }


    auto indicies = new unsigned short[36];
    memcpy_s(indicies, sizeof(g_Indicies), g_Indicies, sizeof(g_Indicies));
    RHIIndexBufferCreateInfo info((uint8*)indicies, sizeof(g_Indicies), IndexBufferElementType::IET_U16);
    IndexBuffer_ = RenderDevice::RHI->CreateIndexBuffer(info);

    VertexDeclarationElement position(VertexElementType::VET_Float3, 0, 0, 0);
    VertexDeclarationElement normal(VertexElementType::VET_Float3, 1, 0, 1);
    VertexDeclarationElement color(VertexElementType::VET_Float3, 2, 0, 2);
    std::vector<VertexDeclarationElement> elements;
    elements.push_back(position);
    elements.push_back(normal);
    elements.push_back(color);

    auto decl = RenderDevice::RHI->CreateVertexDeclaration(elements);
    VertexShader_ = RenderDevice::RHI->CreateVertexShader("Asset/Shaders/VertexColorVS.hlsl");
    PixelShader_ = RenderDevice::RHI->CreatePixelShader("Asset/Shaders/VertexColorPS.hlsl");
    ShaderState_ = RenderDevice::RHI->CreateBoundShaderState(decl, VertexShader_, PixelShader_);
}

void StaticMesh::Render(const RenderSingleViewContext& viewContext, const RenderSingleObjectContext& objectContext)
{
    RenderDevice::RHI->IASetPrimitiveTopology(RHIPrimitiveTopology::TriangleList);

    RenderDevice::RHI->IASetVertexBuffer(0, PositionCmpt_->GetVertexBuffer().get(), PositionCmpt_->GetVertexStrike(), 0);
    RenderDevice::RHI->IASetVertexBuffer(2, ColorCmpt_->GetVertexBuffer().get(), ColorCmpt_->GetVertexStrike(), 0);
    RenderDevice::RHI->IASetIndexBuffer(IndexBuffer_.get(), 0);

    RenderDevice::RHI->SetBoundShaderState(ShaderState_.get());

    RenderDevice::RHI->SetShaderConstantBuffer(VertexShader_.get(), 1, viewContext.RenderView->GetConstantBufferPerView()->GetRHIConstantBuffer());
    RenderDevice::RHI->SetShaderConstantBuffer(VertexShader_.get(), 2, objectContext.ConstantBufferPerObject->GetRHIConstantBuffer());

    RenderDevice::RHI->DrawIndexedPrimitive(36, 0, 0);
}


