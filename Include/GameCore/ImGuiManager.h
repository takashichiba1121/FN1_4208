#pragma once
#include <string>
#include "Vector2.h"

class ImGuiManagerInterface
{
public:
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Finalize() {};
	virtual void NewGui(const std::string& titleName) {};
	virtual void Text(const std::string& text) {};
	virtual void DragInt(const std::string& label, int32_t& value, int32_t min = 0, int32_t max = 0) {};
	virtual void DragFloat(const std::string& label, float& value, float speed = 1.f, float min = 0, float max = 0) {};
	virtual void DragFloat2(const std::string& label, Vector2& value, float speed = 1.f, float min = 0, float max = 0) {};
	virtual bool TreeNode(const std::string& label) { return false; };
	virtual void EndTreeNode() {};
	virtual bool CollapsingHeader(const std::string& label) { return false; };
	virtual bool Button(const std::string& label) { return false; };
	virtual void CheckBox(const std::string& label, bool& value) {};
	virtual void ColorEdit3(const std::string& label, int32_t& color) {};
	virtual void EndGui() {};
};


class ImGuiManager :public ImGuiManagerInterface
{
private:
	ImGuiManager() {}
	ImGuiManager(const ImGuiManager&) {}
	ImGuiManager& operator=(const ImGuiManager&) {}
	~ImGuiManager() {}

public:
	static ImGuiManager* GetInstance();
#ifdef _DEBUG
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
	void NewGui(const std::string& titleName)override;
	void Text(const std::string& text)override;
	void DragInt(const std::string& label, int32_t& value, int32_t min = 0, int32_t max = 0)override;
	void DragFloat(const std::string& label, float& value, float speed = 1.f, float min = 0, float max = 0)override;
	void DragFloat2(const std::string& label, Vector2& value, float speed = 1.f, float min = 0, float max = 0)override;
	bool TreeNode(const std::string& label)override;
	void EndTreeNode()override;
	bool CollapsingHeader(const std::string& label)override;
	bool Button(const std::string& label)override;
	void CheckBox(const std::string& label, bool& value)override;
	void ColorEdit3(const std::string& label, int32_t& color)override;
	void EndGui()override;

#endif
};
