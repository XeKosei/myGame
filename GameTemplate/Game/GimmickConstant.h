#pragma once
namespace nsHikageri
{
	namespace nsGimmick
	{
		namespace nsChandelierConstant
		{
			static const float CHANDELIER_LIGHT_RANGE = 10000.0f;	//�V�����f���A�̌��͈̔�
			static const int CHANDELIER_ADD_STRESS_SPEED = 1;	//�V�����f���A�̌����G�l�~�[�ɃX�g���X��^���鑬��
		}

		namespace nsDoorConstant
		{
			static const float DOOR_OPEN_SPEED = 0.05f;	//�h�A���J���鑬��
			static const float MAX_DOOR_OPNE_ANGLE = 3.141592 / 2;	//�h�A���J���ő�p�x(90�x)
		}
		namespace nsEyeWallConstant
		{
			static const int INI_DESAPPER_INTERVAL = 30;	//�����n�߂�܂ł̃C���^�[�o��
			static const float DISAPPER_SPEED = 0.000001f;	//�����鑬��
			static const float DISAPPER_SPEED_MUL_VALUE = 0.3f;	//�����鑬���ɂ�����l	
		}
	}
}