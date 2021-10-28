#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 INI_FLASHLIGHT_COLOR = { 30.0f,30.0f,30.0f };	//�����d���̏����J���[
			static const float INI_FLASHLIGHT_RANGE = 3000.0f;					//�����d���̏����e���͈�
			static const float INI_FLASHLIGHT_ANGLE = 0.5f;					//�����d���̏����ˏo�p�x
			static const Vector3 APPLY_FLASHLIGHT_POS_VALUE = { 1.8f, 0.8f, 3.0f };	//�����d���̈ʒu���v�Z���邽�߂̒l
			static const int TO_SPOTLIGHTCAMERA_TARGET_DIS = 100;				//�X�|�b�g���C�g�̒����_�܂ł̋���
		}

		namespace nsFlashLightActionConstant
		{
			static const float FLASHLIGHT_ANGLE_ADJUST_SPEED = 0.01f;	//�����d���̎ˏo�p�x�𒲐߂��鑬�x
		}

		namespace nsAbilityStrobeFlash
		{
			static const int INI_STROBEFLASH_CHARGE_COUNT = 50;	//�X�g���{�t���b�V���̃`���[�W���Ԃ̏����l
			static const Vector3 INI_STROBEFLASH_COLOR = {150.0f,150.0f,150.0f};	//�X�g���{�t���b�V���̖��邳�̏����l
			static const Vector3 STROBEFLASH_COLOR_DECREASE_SPEED = {1.5f,1.5f,1.5f};	//�X�g���{�t���b�V���̖��邳�������鑬��
		}

		namespace nsFlashLightBattery
		{
			static const float MAX_BATTERY_LEVEL = 100.0f;	//�ő�o�b�e���[�c��
			static const float BATTERY_LEVEL_DECREASE_SPEED = 0.001f; //�o�b�e���[�̌��鑬�x
 
		}
	}
}