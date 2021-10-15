#include "stdafx.h"
#include "FlashLightInclude.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightActionConstant;

		FlashLightAction::~FlashLightAction()
		{

		}
		bool FlashLightAction::Start()
		{
			return true;
		}

		//FlashLight.cpp�Ŗ��t���[���Ă΂�鏈��
		void FlashLightAction::ExecuteUpdate()
		{
			//�{�^���������ꂽ��
			if (g_pad[0]->IsTrigger(enButtonRB1))
			{
				//�����d���̓d���̃X�C�b�`��؂�ւ���B
				SwitchOnOff();
			}

			if (GetFlashFlag() == true)
			{
				//�\���{�^���̏㉺�ŁA�����d���̎ˏo�p�x�𒲐߂ł���B
				if (g_pad[0]->IsPress(enButtonUp))
				{
					m_flashLight->SetFlashLightAngle(m_flashLight->GetFlashLightAngle() + FLASHLIGHT_ANGLE_ADJUST_SPEED);
				}
				if (g_pad[0]->IsPress(enButtonDown))
				{
					m_flashLight->SetFlashLightAngle(m_flashLight->GetFlashLightAngle() - FLASHLIGHT_ANGLE_ADJUST_SPEED);
				}
			}
		}

		void FlashLightAction::SwitchOnOff()
		{
			//�����d���̓d���̃X�C�b�`��؂�ւ���
			SetFlashFlag(!GetFlashFlag());

			//�d����ON�Ȃ��
			if (GetFlashFlag() == true)
			{
				//ON�Ȃ�Ήe���͈͂�ݒ�
				m_flashLight->GetSpotLight()->SetRange(nsFlashLightConstant::INI_FLASHLIGHT_RANGE);

			}
			//�d����OFF�Ȃ��
			else
			{
				//OFF�Ȃ�Ήe���͈͂�0�ɂ���B
				m_flashLight->GetSpotLight()->SetRange(0.0f);
			}
		}
	}
}