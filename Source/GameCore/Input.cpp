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
