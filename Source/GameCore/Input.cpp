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
}

bool Input::GetKey(const KEY& key)
{
	return instance_->keys_[(uint8_t)key];
}

bool Input::GetKeyTrigger(const KEY& key)
{
	return instance_->keys_[(uint8_t)key] && !instance_->oldkeys_[(uint8_t)key];
}

bool Input::GetKeyRelease(const KEY& key)
{
	return !instance_->keys_[(uint8_t)key] && instance_->oldkeys_[(uint8_t)key];
}