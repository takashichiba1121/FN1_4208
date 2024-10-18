#pragma once
#include <string>
#include "Vector2.h"

class ImGuiManager
{
private:
	ImGuiManager() {}
	ImGuiManager(const ImGuiManager&) {}
	ImGuiManager& operator=(const ImGuiManager&) {}
	~ImGuiManager() {}

public:
	static ImGuiManager* GetInstance();
	void Initialize();
	void Update();
	void Draw();
	void End();
	void Finalize();
};
