#include "stdafx.h"
#include "FlashLightAction.h"
#include "FlashLight.h"
#include "FlashLightConstant.h"

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

			if (m_flashLight->GetFlashFlag() == true)
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
			
			ChargeFlashPrepare();
			
			if (m_chargeFlashFlag == true)
			{
				ChargeFlash();
			}
		}

		void FlashLightAction::SwitchOnOff()
		{
			//�����d���̓d���̃X�C�b�`��؂�ւ���
			m_flashLight->SetFlashFlag(!m_flashLight->GetFlashFlag());

			//�d����ON�Ȃ��
			if (m_flashLight->GetFlashFlag() == true)
			{
				//ON�Ȃ�Ήe���͈͂�ݒ�
				m_flashLight->GetSpotLight()->SetRange(nsFlashLightConstant::FLASHLIGHT_INI_RANGE);

			}
			//�d����OFF�Ȃ��
			else
			{
				//OFF�Ȃ�Ήe���͈͂�0�ɂ���B
				m_flashLight->GetSpotLight()->SetRange(0.0f);
			}
		}

		void FlashLightAction::ChargeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				if (m_chargeCount < 50)
				{
					m_chargeCount++;
				}
			}
			else 
			{
				if (m_chargeCount >= 50)
				{
					m_chargeFlashFlag = true;
				}
				m_chargeCount = 0;
			}
		}

		void FlashLightAction::ChargeFlash()
		{
			m_flashLight->GetSpotLight()->SetColor(m_chargeFlashColor);

			m_chargeFlashColor -= {1.0f, 1.0f, 1.0f};

			if (m_chargeFlashColor.x <= 10.0f)
			{
				m_chargeFlashFlag = false;
				m_chargeFlashColor = { 100.0f, 100.0f, 100.0f };
			}
		}
	}
}