#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "ItemKey.h"
#include "Door.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsAbilityMedousaEyeConstant;

		AbilityMedousaEye::~AbilityMedousaEye()
		{

		}

		void AbilityMedousaEye::Init(FlashLight* flashLight)
		{
			m_flashLight = flashLight;

			m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

			//�G�t�F�N�g
			m_chargingEff.Init(u"Assets/effect/StrobeFlashEff.efk");
			m_chargingEff.SetScale(INI_MEDOUSAEYEFLASH_EFF_SCALE);

		}
		void AbilityMedousaEye::ExecuteUpdate()
		{
			if (m_abilityAcitveFlag == false)
				return;

			//�����d�������Ă���Ƃ��B
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn())
			{
				//���h�D�[�T�A�C�̃`���[�W���I�������
				if (m_medousaEyeChargeCount <= 0)
				{
					//�{�^���������
					if (g_pad[0]->IsPress(enButtonRB2) == false)
					{
						//�G���X�g���{�t���b�V�����󂯂ċ���ł���Ȃ��
						if (m_abilityManager->GetEnemy()->GetEnemyState() == nsEnemy::Enemy::enState_Flinch)
						{
							//�Ή�������
							m_abilityManager->GetEnemy()->SetEnemyState(nsEnemy::Enemy::enState_Petrifaction);
							//���𗎂Ƃ�(��)
							nsItem::ItemKey* itemKey = NewGO<nsItem::ItemKey>(0);
							itemKey->SetPlayer(m_flashLight->GetPlayer());
							itemKey->SetKeyColor(nsGimmick::Door::enDoorColor_White);
							itemKey->SetPosition(m_abilityManager->GetEnemy()->GetEnemyMove()->GetPosition());

							m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_MEDOUSAEYEFLASH_BATTERY_COST);

							Reset();
						}
					}
				}
				//�X�g���{�t���b�V���̃`���[�W���������Ă�����A
				if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge())
				{
					//�G�t�F�N�g�̍Đ�
					if (m_chargingEff.IsPlay() == false)
					{
						m_chargingEff.Play();
					}
					m_chargingEff.SetPosition(m_flashLight->GetModelPos());
					m_chargingEff.Update();

					//���h�D�[�T�A�C�̃`���[�W���s���B
					if (m_medousaEyeChargeCount > 0)
					{
						m_medousaEyeChargeCount--;
					}
				}
				else
				{
					Reset();
				}
			}
			else
			{
				Reset();
			}
		}

		void AbilityMedousaEye::Reset()
		{
			//�G�t�F�N�g���~
			m_chargingEff.Stop();
			//���h�D�[�T�A�C�̃J�E���g��0�ɁB
			m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;
		}
	}
}