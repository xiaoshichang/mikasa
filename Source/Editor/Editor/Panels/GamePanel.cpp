
#include "GamePanel.h"
#include "Runtime/Framework/GameViewClient/GameViewClient.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "Runtime/Core/Render/RenderDevice/RHI/DX11/RHIShaderResourceViewDX11.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/RenderTarget.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;

GamePanel::GamePanel() : Panel("Game")
{

}

void GamePanel::Init()
{

}

void GamePanel::UnInit() {

}

void GamePanel::RenderContent()
{
    GameViewClient::Render();
    auto rtv = GameViewClient::GetSceneColorRT();
    auto srv = (RHIShaderResourceViewDX11*)rtv->AsShaderResourceView();
    auto texture = (ImTextureID)srv->GetInternal();
    auto width = 1024 * 0.6;
    auto height = 768 * 0.6;

    ImGui::Text("---");
    ImGui::Image(texture, ImVec2((float)width, (float)height), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));
    ImGui::Text("---");
}


