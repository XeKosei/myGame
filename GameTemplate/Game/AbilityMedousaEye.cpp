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

		bool AbilityMedousaEye::Start()
		{
			m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

			return true;
		}
		void AbilityMedousaEye::ExecuteUpdate()
		{
			if (m_abilityAcitveFlag == false)
				return;

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
						//���h�D�[�T�A�C�̃J�E���g��0�ɁB
						m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

						m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_MEDOUSAEYEFLASH_BATTERY_COST);
					}
				}
			}
			//�X�g���{�t���b�V���̃`���[�W���������Ă�����A
			if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge())
			{
				//���h�D�[�T�A�C�̃`���[�W���s���B
				if (m_medousaEyeChargeCount > 0)
				{
					m_medousaEyeChargeCount--;
				}
			}
			else
			{
				//���h�D�[�T�A�C�̃J�E���g��0�ɁB
				m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;
			}
		}
	}
}