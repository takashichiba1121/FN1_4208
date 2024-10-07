#include "Input.h"

void Input::Initialize()
{
	static Input i;
	instance_ = &i;
}

void Input::Update()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (size_t i = 0; i < instance_->keys_.size(); i++)
	{
		instance_->oldkeys_[i] = instance_->keys_[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
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