#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 INI_FLASHLIGHT_COLOR = { 5.0f,5.0f,5.0f };	//�����d���̏����J���[
			static const float INI_FLASHLIGHT_RANGE = 10000.0f;					//�����d���̏����e���͈�
			static const float INI_FLASHLIGHT_ANGLE = 1.0f;					//�����d���̏����ˏo�p�x
			static const Vector3 INI_FLASHLIGHT_MODEL_SCALE = { 1.5f,1.5f,1.5f };	//�����d���̃��f���̃X�P�[��
			static const Vector3 FLASHLIGHT_MODEL_POS_APPLY_VALUE = { 1.8f, -1.2f, 3.0f };	//�����d���̃��f���̈ʒu���v�Z���邽�߂̒l
			static const Vector3 FLASHLIGHT_POS_APPLY_VALUE = { 50.0f, -20.0f, 0.0f };	//�����d���̖{���̈ʒu���v�Z���邽�߂̒l
			static const int TO_SPOTLIGHTCAMERA_TARGET_DIS = 100;				//�X�|�b�g���C�g�̒����_�܂ł̋���
		}

		namespace nsFlashLightActionConstant
		{
			static const float FLASHLIGHT_ANGLE_ADJUST_SPEED = 0.01f;	//�����d���̎ˏo�p�x�𒲐߂��鑬�x
		}

		namespace nsFlashLightBatteryConstant
		{
			static const float MAX_BATTERY_LEVEL = 100.0f;	//�ő�o�b�e���[�c��
			static const float BATTERY_LEVEL_DECREASE_SPEED = 0.01f; //�o�b�e���[�̌��鑬�x
		}

		namespace nsAbilityStrobeFlashConstant
		{
			static const int INI_STROBEFLASH_CHARGE_COUNT = 60;	//�X�g���{�t���b�V���̃`���[�W���Ԃ̏����l
			static const Vector3 INI_STROBEFLASH_COLOR = {50.0f,50.0f,50.0f};	//�X�g���{�t���b�V���̖��邳�̏����l
			static const Vector3 STROBEFLASH_COLOR_DECREASE_SPEED = {1.0f,1.0f,1.0f};	//�X�g���{�t���b�V���̖��邳�������鑬��
			static const float INI_STROBEFLASH_BATTERY_COST = 20.0f;	//�X�g���{�t���b�V���ŏ����o�b�e���[�̃R�X�g
			
			static const Vector3 INI_STROBEFLASH_EFF_SCALE = {0.5f,0.5f,0.5f};	//�G�t�F�N�g�̑傫��
		}

		namespace nsAbilityClairvoyanceConstant
		{
			static const float INI_CLAIRVOYANCE_BATTERY_COST = 0.05f;	//�N���A�{�����X�ŏ����o�b�e���[(���������t���[��)
			static const int PLAY_CLAIRVOYANCE_SE_INTERVAL = 80;	//SE���Đ�����Ԋu
		}

		namespace nsAbilityMedousaEyeConstant
		{
			static const int INI_MEDOUSAEYEFLASH_CHARGE_COUNT = 75;	//���h�D�[�T�A�C�̃`���[�W���Ԃ̏����l
			static const Vector3 INI_MEDOUSAEYEFLASH_COLOR = { 50.0f,50.0f,50.0f };	//���h�D�[�T�A�C�̖��邳�̏����l
			static const float  INI_MEDOUSAEYEFLASH_BATTERY_COST = 20.0f;	//���h�D�[�T�A�C�ŏ����o�b�e���[�̃R�X�g
			static const Vector3 INI_MEDOUSAEYEFLASH_EFF_SCALE = { 0.8f,0.8f,0.8f };	//�G�t�F�N�g�̑傫��
		}
	}
}