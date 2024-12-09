#pragma once
#include "ISceneChange.h"
#include "Vector2.h"


class BasicSceneChange :public ISceneChange
{
public:
	BasicSceneChange();
	~BasicSceneChange();

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

	template<typename T>
	T easeInQuint(T start, T end, float time)
	{
		return start + (time * time * time * time * time) * (end - start);
	}

	template<typename T>
	T easeOutQuad(T start, T end, float time)
	{
		return start + (1 - (1 - time) * (1 - time)) * (end - start);
	}

private:

	

	bool isStart_ = false;

	bool isClose_ = false;

	bool isOpenStart_ = false;

	bool isEnd_ = false;

	float y_ = 0;

	float moveTimer_ = 0;
	float moveMaxTime_ = 30;

	

	float afterTimer = 0;
	float afterMaxTime = 20;




};