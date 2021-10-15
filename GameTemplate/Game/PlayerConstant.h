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
			static const float PLAYER_WALK_SPEED = 3.0f;	//�v���C���[�̕�������
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 1.5f;//�v���C���[�̑��鑬��
			static const float PLAYER_CROUCHDOWN_WALK_SPEED = PLAYER_WALK_SPEED / 2.0f;//�v���C���[�̋��ݕ����̑���
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//�v���C���[�������Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 0.05f;		//�J��������������
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
		}
	}
}
