#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using  namespace nsAbilityStrobeFlashConstant;

		bool AbilityStrobeFlash::Start()
		{
			//�X�g���{�t���b�V���̖��邳��ݒ�
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			return true;
		}

		void AbilityStrobeFlash::ExecuteUpdate()
		{
			//�����d�������Ă���Ƃ��B
			if (m_flashLight->GetFlashLightAction()->GetFlashFlag())
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
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_STROBEFLASH_BATTERY_COST);
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

			if (m_strobeFlashColor.x == INI_STROBEFLASH_COLOR.x)
			{
				QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
					{
						//�����d���̌���
						Vector3 strobeDir = m_flashLight->GetFlashLightDir();
						strobeDir.Normalize();

						//�t���b�V�����G�l�~�[�̐��ʂɓ������Ă���Ȃ��
						if (Dot(strobeDir, enemy->GetEnemyMove()->GetDirection()) <= 0.0f)
						{
							//�G�̓��ւ̌���
							Vector3 toHeadDir = enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head") - m_flashLight->GetFlashLightPos();
							toHeadDir.Normalize();

							//��̃x�N�g���̓��ς��Z�o
							float dot = Dot(toHeadDir, strobeDir);

							//�����d���̎ˏo�p�x����A
							float flashLightAngle = m_flashLight->GetFlashLightAngle();
							flashLightAngle /= 2;	//���a�̎ˏo�p�x���~�����̂ŁA2�Ŋ���
							flashLightAngle /= 3.141592;	//�~�����Ŋ��邱�ƂŁA0�`1�͈̔͂ɁB
							flashLightAngle = 1 - flashLightAngle;

							//���ς��ˏo�p�x���������Ȃ��
							if (dot >= flashLightAngle)
							{
								enemy->SetEnemyState(nsEnemy::Enemy::enState_Flinch);
							}
						}
						return true;
					}
				);
			}

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