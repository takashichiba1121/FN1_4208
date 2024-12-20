#include "ImGuiManager.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "DxLib.h"
#include "strconv.h"

ImGuiManager* ImGuiManager::GetInstance()
{
	static ImGuiManager inst;
	return &inst;
}

void ImGuiManager::Initialize()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows　★ここ消すとマルチウィンドウ解除

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
	ImGui_ImplDX11_Init((ID3D11Device*)DxLib::GetUseDirect3D11Device(), (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());
}

void ImGuiManager::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
}

void ImGuiManager::Draw()
{
	RefreshDxLibDirect3DSetting();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	RefreshDxLibDirect3DSetting();
}

void ImGuiManager::End()
{
	ImGui::Render();
}

void ImGuiManager::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}