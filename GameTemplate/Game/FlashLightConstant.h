#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 FLASHLIGHT_INI_COLOR = { 10.0f,10.0f,10.0f };	//�����d���̏����J���[
			static const float FLASHLIGHT_INI_RANGE = 3000.0f;					//�����d���̏����e���͈�
			static const float FLASHLIGHT_INI_ANGLE = 0.5f;					//�����d���̏����ˏo�p�x
			static const Vector3 APPLY_FLASHLIGHT_POS_VALUE = { 1.8f, 0.8f, 3.0f };	//�����d���̈ʒu���v�Z���邽�߂̒l
			static const int TO_SPOTLIGHTCAMERA_TARGET_DIS = 100;				//�X�|�b�g���C�g�̒����_�܂ł̋���
		}

		namespace nsFlashLightActionConstant
		{
			static const float FLASHLIGHT_ANGLE_ADJUST_SPEED = 0.01f;	//�����d���̎ˏo�p�x�𒲐߂��鑬�x
		}
	}
}