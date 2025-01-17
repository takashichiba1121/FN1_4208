#include"Inversion.h"
#include"Input.h"
#include"StageManager.h"
#include"Water.h"
#include"StageManager.h"

void Inversion::Initialize() {
	
}

void Inversion::Update() {

	endInversion = false;

	//�L�[����Ŕ��]
	if (!Water::GetInstance()->GetIsChangeHorizontal() && !StageManager::GetInstance()->GetIsClear()) {

		if (!Input::GetIsUsePad())
		{
			if (Input::GetKeyTrigger(Input::Key::Q)) {
				isInversion = true;
			}
		}
		else
		{
			//�p�b�g����X�{�^��
			if (Input::TriggerPadKey(PAD_INPUT_3))
			{
				isInversion = true;
			}
		}

		
	}

	//���]���̏���
	if (isInversion) {

		frame++;	//�t���[����i�߂�
		//�������̃C�[�W���O
		horizontalPos = easeStartPos + Easing(frame / MaxFrame) * (easeEndPos - easeStartPos);
		Water::GetInstance()->SetHorizontal(horizontalPos);
		StageManager::GetInstance()->Inversion(Easing(frame / MaxFrame));
		
		//�C�[�W���O�I����̏���
		if (frame >= MaxFrame) {
			isInversion = false;
			endInversion = true;
			frame = 0.0f;
			isFront = !isFront;
			horizontalPos = Water::GetInstance()->GetHorizontal();

  			ResetEasing();
		}
	}
	else {
		ResetEasing();
	}

	//���̔��]����
	Water::GetInstance()->Inversion(Easing(frame / MaxFrame), isFront);

}

void Inversion::ResetEasing() {
	//�C�[�W���O�����n�_��ݒ�
	easeStartPos = Water::GetInstance()->GetHorizontal();
	//�C�[�W���O�I���n�_��ݒ�
	easeEndPos = WIN_HEIGHT / 2 + (WIN_HEIGHT / 2 - Water::GetInstance()->GetHorizontal());

	StageManager::GetInstance()->SetTentPos();
}

Inversion* Inversion::GetInstance()
{
	static Inversion instance;
	return &instance;
}