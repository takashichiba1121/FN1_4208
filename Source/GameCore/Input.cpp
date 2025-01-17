#include "Input.h"

void Input::Initialize()
{
	static Input i;
	instance_ = &i;
}

void Input::Update()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (size_t i = 0; i < instance_->keys_.size(); i++)
	{
		instance_->oldkeys_[i] = instance_->keys_[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(instance_->keys_.data());

	instance_->oldMouseKeys_= instance_->mouseKeys_;

	instance_->mouseKeys_=GetMouseInput();

	int32_t x=0;
	int32_t y = 0;

	GetMousePoint(&x,&y);

	instance_->mousePos_ = { (float)x,(float)y };

	instance_->mouseWheel_=GetMouseWheelRotVolF();

	instance_->oldPadkey = instance_->PadKey;

	instance_->PadKey = GetJoypadInputState(DX_INPUT_PAD1);

	GetJoypadAnalogInput(&instance_->padX, &instance_->padY, DX_INPUT_PAD1);

	if (CheckHitKeyAll(DX_CHECKINPUT_PAD))
	{
		instance_->isUsePad_ = true;
	}
	else if (CheckHitKeyAll(DX_CHECKINPUT_KEY) || CheckHitKeyAll(DX_CHECKINPUT_MOUSE))
	{
		instance_->isUsePad_ = false;
	}

	
}

bool Input::GetKey(const Key& key)
{
	return instance_->keys_[(uint8_t)key];
}

bool Input::GetKeyTrigger(const Key& key)
{
	return instance_->keys_[(uint8_t)key] && !instance_->oldkeys_[(uint8_t)key];
}

bool Input::GetKeyRelease(const Key& key)
{
	return !instance_->keys_[(uint8_t)key] && instance_->oldkeys_[(uint8_t)key];
}

bool Input::GetMouseKey(const MouseKey& key)
{
	return instance_->mouseKeys_ & (uint32_t)key;
}

bool Input::GetMouseKeyTrigger(const MouseKey& key)
{
	return instance_->mouseKeys_ & (uint32_t)key && !(instance_->oldMouseKeys_ & (uint32_t)key);
}

bool Input::GetMouseKeyRelease(const MouseKey& key)
{
	return !(instance_->mouseKeys_ & (uint32_t)key) && (instance_->oldMouseKeys_ & (uint32_t)key);;
}

Vector2 Input::GetMousePos()
{
	return instance_->mousePos_;
}

float Input::GetMouseWheel()
{
	return instance_->mouseWheel_;
}

bool Input::PushPadKey(uint16_t keyNumber)
{
	//指定キーを押していればtrueを返す
	if (instance_->PadKey & keyNumber)
	{
		return true;
	}
	//そうでなければfalse返す
	return false;
}

bool Input::TriggerPadKey(uint16_t keyNumber)
{
	//指定キーを押していればtrueを返す
	if (instance_->PadKey & keyNumber && !(instance_->oldPadkey & keyNumber))
	{
		return true;
	}
	//そうでなければfalse返す
	return false;
}

bool Input::ReleasePadKey(uint16_t keyNumber)
{
	//指定キーを押していればtrueを返す
	if (!(instance_->PadKey & keyNumber) && instance_->oldPadkey & keyNumber)
	{
		return true;
	}
	//そうでなければfalse返す
	return false;
}

uint32_t Input::PadX()
{
	return instance_->padX;
}

uint32_t Input::PadY()
{
	return instance_->padY;
}

bool Input::GetIsUsePad()
{
	return instance_->isUsePad_;
}
