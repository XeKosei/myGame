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
		void FlashLightAction::Init(FlashLight* flashLight)
		{
			m_flashLight = flashLight;
		}

		//FlashLight.cpp�Ŗ��t���[���Ă΂�鏈��
		void FlashLightAction::ExecuteUpdate()
		{
			//�{�^���������ꂽ��
			if (g_pad[0]->IsTrigger(enButtonRB1))
			{
				//�����d���̓d���̃X�C�b�`��؂�ւ���B
				SwitchOnOff();
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/FlashLightSwitch.wav");
				ss->Play(false);
			}

			if (GetIsFlashLightSwitchOn() == true)
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
			if (m_flashLight->GetFlashLightBattery()->GetBatteryLevel() > 0.0f)
			{
				//�����d���̓d���̃X�C�b�`��؂�ւ���
				SetIsFlashLightSwitchOn(!GetIsFlashLightSwitchOn());
				//�d����OFF�������Ƃ�
				if (GetIsFlashLightSwitchOn() == false)
				{	
					//OFF�Ȃ�Ήe���͈͂�0�ɂ���B
					m_flashLight->GetSpotLight()->SetRange(0.0f);
				}
				else
				{
					//ON�Ȃ�Ήe���͈͂�ݒ�
					m_flashLight->GetSpotLight()->SetRange(nsFlashLightConstant::INI_FLASHLIGHT_RANGE);
				}
			}
			else
			{
				//�d����ON�������Ƃ�
				if (GetIsFlashLightSwitchOn() == true)
				{
					//�����d���̓d���̃X�C�b�`��؂�ւ���
					SetIsFlashLightSwitchOn(!GetIsFlashLightSwitchOn());
					//ON�Ȃ�Ήe���͈͂�ݒ�
					m_flashLight->GetSpotLight()->SetRange(0.0f);

				}
			}
		}
	}
}