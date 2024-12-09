#pragma once
class ISceneChange
{
public:
	virtual ~ISceneChange() {};

	//������
	virtual void Initialize() {};

	//�I������
	virtual void Finalize() {};

	//���t���[���X�V
	virtual void Update() {};

	//�`��
	virtual void Draw() {};

	virtual bool GetIsStart() { return isStart_; };
	virtual void SetIsStart(bool flag) { isStart_ = flag; };

	virtual bool GetIsClose() { return isClose_; };
	virtual void SetIsClose(bool flag) { isClose_ = flag; };

	virtual bool GetIsOpenStart() { return isOpenStart_; };
	virtual void SetIsOpenStart(bool flag) { isOpenStart_ = flag; };

	virtual bool GetIsEnd() { return isEnd_; };
	virtual void SetIsEnd(bool flag) { isEnd_ = flag; };

private:

	bool isStart_ = false;

	bool isClose_ = false;

	bool isOpenStart_ = false;

	bool isEnd_ = false;

};