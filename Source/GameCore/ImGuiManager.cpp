#include "ImGuiManager.h"

ImGuiManager* ImGuiManager::GetInstance()
{
	static ImGuiManager inst;
	return &inst;
}

#ifdef _DEBUG

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "DxLib.h"
#include "strconv.h"

void ImGuiManager::Initialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows　★ここ消すとマルチウィンドウ解除


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
	ImGui_ImplDX11_Init((ID3D11Device*)DxLib::GetUseDirect3D11Device(), (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());
	io.Fonts->AddFontFromFileTTF("DebugDatas/Fonts/YuGothM.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
}

void ImGuiManager::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::Draw()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	RefreshDxLibDirect3DSetting();
}

void ImGuiManager::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::NewGui(const std::string& titleName)
{
	ImGui::Begin(ansi_to_utf8(titleName).c_str(), (bool*)false);
}

void ImGuiManager::Text(const std::string& text)
{
	ImGui::Text(ansi_to_utf8(text).c_str());
}

void ImGuiManager::DragInt(const std::string& label, int32_t& value, int32_t min, int32_t max)
{
	ImGui::DragInt(ansi_to_utf8(label).c_str(), &value, 1.0f, min, max);
}

void ImGuiManager::DragFloat(const std::string& label, float& value, float speed, float min, float max)
{
	ImGui::DragFloat(ansi_to_utf8(label).c_str(), &value, speed, min, max);
}

void ImGuiManager::DragFloat2(const std::string& label, Vector2& value, float speed, float min, float max)
{
	float f[2] = { value.x,value.y };
	ImGui::DragFloat2(ansi_to_utf8(label).c_str(), f, speed, min, max);
	value = Vector2(f[0], f[1]);
}

bool ImGuiManager::TreeNode(const std::string& label)
{
	return ImGui::TreeNode(ansi_to_utf8(label).c_str());
}

void ImGuiManager::EndTreeNode()
{
	ImGui::TreePop();
}

bool ImGuiManager::CollapsingHeader(const std::string& label)
{
	return ImGui::CollapsingHeader(ansi_to_utf8(label).c_str());
}

bool ImGuiManager::Button(const std::string& label)
{
	return ImGui::Button(ansi_to_utf8(label).c_str());
}

void ImGuiManager::CheckBox(const std::string& label, bool& value)
{
	ImGui::Checkbox(ansi_to_utf8(label).c_str(), &value);
}

void ImGuiManager::ColorEdit3(const std::string& label, int32_t& color)
{
	float r = static_cast<float>((color >> 16) & 0xFF) / 255.0f;
	float g = static_cast<float>((color >> 8) & 0xFF) / 255.0f;
	float b = static_cast<float>(color & 0xFF) / 255.0f;
	float f[3] = { r,g,b };
	ImGui::ColorEdit3(ansi_to_utf8(label).c_str(), f);
	int32_t ri = static_cast<int32_t>(f[0] * 255.0f) << 16;
	int32_t gi = static_cast<int32_t>(f[1] * 255.0f) << 8;
	int32_t bi = static_cast<int32_t>(f[2] * 255.0f);
	color = (ri | gi | bi);
}

void ImGuiManager::EndGui()
{
	ImGui::End();
}

#endif