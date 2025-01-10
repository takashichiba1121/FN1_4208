#pragma once
#include"cmath"
#include<memory>

class ClearManager {

#pragma region Singleton

public:

	ClearManager() {};

	ClearManager(const ClearManager& carManager) = delete;

	ClearManager& operator=(const ClearManager& carManager) = delete;

	static ClearManager* GetInstance();
#pragma endregion

	void SetIsClear(const bool flag) { isClear = flag; }
	bool GetIsClear() { return isClear; }

private:

	bool isClear = false;

};