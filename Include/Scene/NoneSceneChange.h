#pragma once
#include "ISceneChange.h"

class NoneSceneChange :public ISceneChange
{
public:
	NoneSceneChange();
	~NoneSceneChange();

	//初期化
	void Initialize()override;

	//終了処理
	void Finalize()override;

	//毎フレーム更新
	void Update()override;

	//描画
	void Draw()override;

	bool GetIsStart() { return isStart_; };
	void SetIsStart(bool flag) { isStart_ = flag; };

	bool GetIsClose() { return isClose_; };
	void SetIsClose(bool flag) { isClose_ = flag; };

	bool GetIsOpenStart() { return isOpenStart_; };
	void SetIsOpenStart(bool flag) { isOpenStart_ = flag; };

	bool GetIsEnd() { return isEnd_; };
	void SetIsEnd(bool flag) { isEnd_ = flag; };

private:



private:



	bool isStart_ = false;

	bool isClose_ = false;

	bool isOpenStart_ = false;

	bool isEnd_ = false;

	




};