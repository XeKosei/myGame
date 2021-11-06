#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const Vector3 INI_PLAYER_POSITION = { 1000.0f,0.0f,0.0f };	//�v���C���[�̏����ʒu
			static const float PLAYER_MODEL_WIDTH = 10.0f;	//�v���C���[�̃��f���̉���
			static const float PLAYER_MODEL_HEIGHT = 120.0f;	//�v���C���[�̃��f���̍���
			static const Vector3 INI_PLAYER_SCALE = { 1.0f, 1.0f, 1.0f };	//�v���C���[�̃��f���̑傫���̏����l
		}
		//Player�N���X�ŗ��p����萔
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 80.0f;	//�v���C���[�̕�������
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 2.0f;//�v���C���[�̑��鑬��
			static const float PLAYER_CROUCHDOWN_WALK_SPEED = PLAYER_WALK_SPEED / 2.0f;//�v���C���[�̋��ݕ����̑���
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//�v���C���[�������Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 3.0f;		//�J��������������
			static const float INI_PLAYER_EYE_HEIGHT = 250.0f;		//�v���C���[�̖ڂ̍���
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//�J�����̃^�[�Q�b�g�ւ̋���

			static const float ADD_EYEHEIGHT_SPEED_IDLE = 0.02f;	//�J�������ċz�ŏ㉺���鑬��
			static const float MAX_ADD_EYEHEIGHT = 2.0f;	//�J�������ċz�ŏ㉺����ő���Z�l
			static const float MIN_ADD_EYEHEIGHT = -2.0f;	//�J�������ċz�ŏ㉺����ŏ����Z�l
		}

		namespace nsPlayerActionConstant
		{
			static const float CROUCHDOWN_PLAYER_EYE_HEIGHT = 100.0f;		//�v���C���[������ł��鎞�̖ڂ̍���
			static const Vector3 CROUCHDOWN_PLAYER_SCALE = { 1.0f, 0.5f, 1.0f };	//�v���C���[�̃��f���̑傫���̏����l
		}

		namespace nsPlayerSanityConstant
		{
			static const float MAX_PLAYER_SANITY = 100.0f;	//�v���C���[��SAN�l�̍ő�l
			static const int DAMAGE_INTERVAL = 200;	//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̊Ԋu
			static const Vector4 INI_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 0.0f };	//Hazy�X�v���C�g�̏����J���[
			static const Vector4 DAMAGED_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };	//�_���[�W���󂯂��ۂ�Hazy�X�v���C�g�̃J���[
			static const float HAZYSPRITE_MUL_COLOR_PINCH = 20.0f;	//�s���`����Hazy�X�v���C�g�̃J���[�Ɋ|����l

			static const float BIG_DAMAGE_LINE = MAX_PLAYER_SANITY / 3;	//��_���[�W���󂯂Ă���Ɣ��f����郉�C��

			static const float ADD_ALPHA_SPEED = 0.001f;	//�X�v���C�g���_�ł��鑬��
			static const float MAX_ADD_ALPHA = 0.02f;		//�_�ł̍ő���Z�l
			static const float MIN_ADD_ALPHA = -0.02f;		//�_�ł̍ŏ����Z�l
		}

		namespace nsPlayerBittenConstant
		{
			static const int INI_CAN_MOVE_INTERVAL = 30;	//������悤�ɂȂ�܂ł̃C���^�[�o��
			static const int RESIST_TO_BITE_NUM = 100;	//���݂��ɒ�R���鐔�l

			
		}

		namespace nsPlayerPouchConstant
		{
			static const std::wstring ITEM_NAME[PlayerPouch::enItem_num] = { L"�d�r", L"���_�����" };

			static const int TRANQUILIZER_RECOVERY_NUM = 50.0f;	//���_����܂��g�������̉񕜗�
		}
	}
}
