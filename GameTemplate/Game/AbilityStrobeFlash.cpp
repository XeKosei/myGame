#include "stdafx.h"
#include "AbilityStrobeFlash.h"
#include "FlashLight.h"
#include "FlashLightConstant.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using  namespace nsAbilityStrobeFlash;

		bool AbilityStrobeFlash::Start()
		{
			//�X�g���{�t���b�V���̖��邳��ݒ�
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			return true;
		}

		void AbilityStrobeFlash::ExecuteUpdate()
		{
			//�����d�������Ă���Ƃ��B
			if (m_flashLight->GetFlashFlag())
			{
				//�X�g���{�t���b�V���̃`���[�W
				StrobeFlashPrepare();

				//�t���O��true�Ȃ�΃X�g���{�t���b�V������
				if (m_strobeFlashFlag == true)
				{
					StrobeFlash();
				}
			}
			//�����d�����������烊�Z�b�g
			else
			{
				m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;
				m_flashLight->GetSpotLight()->SetColor(nsFlashLightConstant::INI_FLASHLIGHT_COLOR);
				m_strobeFlashColor = INI_STROBEFLASH_COLOR;
				m_strobeFlashFlag = false;
			}
		}

		/// @brief �X�g���{�t���b�V���𔭓����鏀���̏���
		void AbilityStrobeFlash::StrobeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				//�J�E���g���I���܂Ńf�N�������g
				if (m_strobeChargeCount > 0)
				{
					m_strobeChargeCount--;
				}
			}
			else
			{
				//�{�^����������Ƃ��ɃJ�E���g���I����Ă�����
				if (m_strobeChargeCount <= 0)
				{
					m_strobeFlashFlag = true;
				}
				//�J�E���g�����Z�b�g
				m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;
			}
		}

		/// @brief �X�g���{�t���b�V���𔭓����鏈��
		void AbilityStrobeFlash::StrobeFlash()
		{
			//�����d���̖��邳��ݒ�
			m_flashLight->GetSpotLight()->SetColor(m_strobeFlashColor);
			//�i�X���邳������
			m_strobeFlashColor -= STROBEFLASH_COLOR_DECREASE_SPEED;

			//�J���[�������l�ɖ߂�����A�X�g���{�t���b�V���̏������I��
			if (m_strobeFlashColor.x <= nsFlashLightConstant::INI_FLASHLIGHT_COLOR.x)
			{
				m_flashLight->GetSpotLight()->SetColor(nsFlashLightConstant::INI_FLASHLIGHT_COLOR);
				m_strobeFlashColor = INI_STROBEFLASH_COLOR;
				m_strobeFlashFlag = false;		
			}
		}

	}
}