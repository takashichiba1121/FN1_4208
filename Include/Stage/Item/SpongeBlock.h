#pragma once
#include"Object.h"
class SpongeBlock :
    public Object
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;
	/// <summary>

	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;



private:

	Vector2 scale = { 3,3 };

	Vector2 normalSize = { 32,32 };
	
};

