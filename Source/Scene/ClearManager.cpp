#include "ClearManager.h"

ClearManager* ClearManager::GetInstance()
{
	static ClearManager instance;
	return &instance;
}