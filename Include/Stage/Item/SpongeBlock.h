#pragma once
#include"Object.h"
class SpongeBlock :
    public Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;
	/// <summary>

	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;



private:

	Vector2 scale = { 3,3 };
	
};

