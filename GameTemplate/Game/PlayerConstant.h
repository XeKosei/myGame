#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const float PLAYER_MODEL_WIDTH = 50.0f;	//�v���C���[�̃��f���̉���
			static const float PLAYER_MODEL_HEIGHT = 100.0f;	//�v���C���[�̃��f���̍���
		}
		//Player�N���X�ŗ��p����萔
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 3.0f;	//�v���C���[�̕�������
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 1.5f;//�v���C���[�̑��鑬��
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//�v���C���[�������Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 0.05f;		//�J��������������
			static const float PLAYER_EYES_HEIGHT = 200.0f;		//�v���C���[�̖ڂ̍���
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//�J�����̃^�[�Q�b�g�ւ̋���
		}

	}
}
