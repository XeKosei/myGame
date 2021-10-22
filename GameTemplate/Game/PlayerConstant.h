#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const Vector3 INI_PLAYER_POSITION = { 1000.0f,0.0f,0.0f };	//�v���C���[�̏����ʒu
			static const float PLAYER_MODEL_WIDTH = 10.0f;	//�v���C���[�̃��f���̉���
			static const float PLAYER_MODEL_HEIGHT = 20.0f;	//�v���C���[�̃��f���̍���
			static const Vector3 INI_PLAYER_SCALE = { 1.0f, 1.0f, 1.0f };	//�v���C���[�̃��f���̑傫���̏����l
		}
		//Player�N���X�ŗ��p����萔
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 100.0f;	//�v���C���[�̕�������
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 2.0f;//�v���C���[�̑��鑬��
			static const float PLAYER_CROUCHDOWN_WALK_SPEED = PLAYER_WALK_SPEED / 2.0f;//�v���C���[�̋��ݕ����̑���
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//�v���C���[�������Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 3.0f;		//�J��������������
			static const float INI_PLAYER_EYE_HEIGHT = 200.0f;		//�v���C���[�̖ڂ̍���
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//�J�����̃^�[�Q�b�g�ւ̋���
		}

		namespace nsPlayerActionConstant
		{
			static const float CROUCHDOWN_PLAYER_EYE_HEIGHT = 100.0f;		//�v���C���[������ł��鎞�̖ڂ̍���
			static const Vector3 CROUCHDOWN_PLAYER_SCALE = { 1.0f, 0.5f, 1.0f };	//�v���C���[�̃��f���̑傫���̏����l
		}

		namespace nsPlayerHPConstant
		{
			static const float MAX_PLAYER_HP = 100.0f;	//�v���C���[�̗̑͂̍ő�l
			static const int DAMAGE_INTERVAL = 200;	//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̊Ԋu
			static const Vector4 INI_BLOODSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 0.0f };	//�_���[�W���󂯂����̉�ʂ̎���̌��̃X�v���C�g�̏����J���[
			
			static const float ADD_RED_SPEED = 0.00001f;	//�X�v���C�g���_�ł��鑬��
			static const float MAX_ADD_RED = 0.0002f;		//�_�ł̍ő���Z�l
			static const float MIN_ADD_RED = -0.0002f;		//�_�ł̍ŏ����Z�l
		}

		namespace nsPlayerBittenConstant
		{
			static const int INI_CAN_MOVE_INTERVAL = 30;	//������悤�ɂȂ�܂ł̃C���^�[�o��
			static const int RESIST_TO_BITE_NUM = 100;	//���݂��ɒ�R���鐔�l

			
		}
	}
}
