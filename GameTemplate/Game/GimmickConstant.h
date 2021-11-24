#pragma once
namespace nsHikageri
{
	namespace nsGimmick
	{
		namespace nsChandelierConstant
		{
			static const float CHANDELIER_FORCE_RANGE = 1000.0f;	//�V�����f���A�̗͂��y�Ԕ͈�
			static const int CHANDELIER_ADD_STRESS_SPEED = 1;	//�V�����f���A�̌����G�l�~�[�ɃX�g���X��^���鑬��
		}

		namespace nsChandelierManagerConstant
		{
			static const int CHANDELIER_NUM = 8;					//�V�����f���A�̐�
			static const Vector3 CHANDELIER_SPOTLIGHT_COLOR = {7.0f,7.0f,7.0f};	//�V�����f���A�̌��̐F
			static const float CHANDELIER_SPOTLIGHT_RANGE = 10000.0f;	//�X�|�b�g���C�g�̌��͈̔�
			static const float CHANDELIER_SPOTLIGHT_ANGLE = 1.5f;		//�V�����f���A�̌��̎ˏo�p�x
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