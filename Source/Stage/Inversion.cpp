#include"Inversion.h"
#include"Input.h"
#include"StageManager.h"
#include"Water.h"

void Inversion::Update() {

	//�L�[����Ŕ��]
	if (Input::GetKeyTrigger(Input::Key::Q)) {
		isInversion = true;
	}

	//���]���̏���
	if (isInversion) {

		frame++;	//�t���[����i�߂�
		//�������̃C�[�W���O
		horizontalPos = easeStartPos + Easing(frame / MaxFrame) * (easeEndPos - easeStartPos);
		Water::GetInstance()->SetHorizontal(horizontalPos);
		
		//�C�[�W���O�I����̏���
		if (frame >= MaxFrame) {
			isInversion = false;
			frame = 0.0f;
			isFront = !isFront;
			horizontalPos = Water::GetInstance()->GetHorizontal();
		}
	}
	else {
	
		//�C�[�W���O�����n�_��ݒ�
		easeStartPos = Water::GetInstance()->GetHorizontal();
		//�C�[�W���O�I���n�_��ݒ�
		easeEndPos = WIN_HEIGHT / 2 + (WIN_HEIGHT / 2 - Water::GetInstance()->GetHorizontal());
	}

	//���̔��]����
	Water::GetInstance()->Inversion(Easing(frame / MaxFrame), isFront);

	//StageManager::GetInstance()->Inversion();


}

Inversion* Inversion::GetInstance()
{
	static Inversion instance;
	return &instance;
}