#pragma once
#include "ISceneChange.h"


class BasicSceneChange :public ISceneChange
{
public:
	BasicSceneChange();
	~BasicSceneChange();

	//������
	void Initialize()override;

	//�I������
	void Finalize()override;

	//���t���[���X�V
	void Update()override;

	//�`��
	void Draw()override;

	bool GetIsStart() { return isStart_; };
	void SetIsStart(bool flag) { isStart_ = flag; };

	bool GetIsClose() { return isClose_; };
	void SetIsClose(bool flag) { isClose_ = flag; };

	bool GetIsOpenStart() { return isOpenStart_; };
	void SetIsOpenStart(bool flag) { isOpenStart_ = flag; };

	bool GetIsEnd() { return isEnd_; };
	void SetIsEnd(bool flag) { isEnd_ = flag; };

	float GetAlpha() { return alpha_; };
	void SetAlpha(float alpha) { alpha_ = alpha; };

private:

	

	bool isStart_ = false;

	bool isClose_ = false;

	bool isOpenStart_ = false;

	bool isEnd_ = false;

	float angle_ = 0;
	float scale_ = 0;

	float scaleTimer_ = 0;
	float scaleMaxTime_ = 30;

	float rotSpeed_ = 0.3f;

	float afterTimer = 0;
	float afterMaxTime = 20;

	float alpha_ = 1.0f;


};