#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "EyeWall.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using  namespace nsAbilityStrobeFlashConstant;

		AbilityStrobeFlash::~AbilityStrobeFlash()
		{

		}

		bool AbilityStrobeFlash::Start()
		{
			m_backGround = FindGO<nsBackGround::BackGround>("backGround");

			//�X�g���{�t���b�V���̖��邳��ݒ�
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			//�X�g���{�t���b�V���̃J�E���g��ݒ�
			m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;

			m_chargingEff.Init(u"Assets/effect/StrobeFlashEff.efk");
			m_chargingEff.SetScale({ 0.7f,0.7f,0.7f });

			return true;
		}

		void AbilityStrobeFlash::ExecuteUpdate()
		{
			if(m_abilityAcitveFlag == false) 
				return;

			//�����d�������Ă���Ƃ��B
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn())
			{
				//�X�g���{�t���b�V���̃`���[�W
				StrobeFlashPrepare();

				//�t���O��true�Ȃ�΃X�g���{�t���b�V������
				if (m_useAbility == true)
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
				m_useAbility = false;
			}
		}

		/// @brief �X�g���{�t���b�V���𔭓����鏀���̏���
		void AbilityStrobeFlash::StrobeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				if (g_pad[0]->IsTrigger(enButtonRB2))
				{
					m_chargingEff.Play();
				}
				m_chargingEff.SetPosition(m_flashLight->GetModelPos());
				m_chargingEff.Update();
				
				//�J�E���g���I���܂Ńf�N�������g
				if (m_strobeChargeCount > 0)
				{
					m_strobeChargeCount--;
				}
			}
			else
			{
				m_chargingEff.Stop();
				//�{�^����������Ƃ��ɃJ�E���g���I����Ă�����
				if (m_strobeChargeCount <= 0)
				{
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_STROBEFLASH_BATTERY_COST);
					m_useAbility = true;
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
				//�����d���̌���
				Vector3 strobeDir = m_flashLight->GetFlashLightDir();
				strobeDir.Normalize();

				//�G�l�~�[
				//�t���b�V�����G�l�~�[�̐��ʂɓ������Ă���Ȃ��
				if (Dot(strobeDir, m_abilityManager->GetEnemy()->GetEnemyMove()->GetDirection()) <= 0.0f)
				{
					//�G�l�~�[�̓����t���b�V���͈̔͂��������ǂ����𒲂ׂ�B
					bool hitFlag = CheckHitFlash(m_abilityManager->GetEnemy()->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head"));
					//true�Ȃ�΃G�l�~�[�����܂���B
					if (hitFlag)
					{
						//���肪���݂���Ԃ������Ȃ�A
						if (m_abilityManager->GetEnemy()->GetEnemyState() == nsEnemy::Enemy::enState_Attack)
						{
							m_abilityManager->GetEnemy()->GetEnemyStress()->AddStress(600.0f);
						}

						//����͋��ށB
						m_abilityManager->GetEnemy()->SetEnemyState(nsEnemy::Enemy::enState_Flinch);				
					}
				}
				//�ڂ̕�
				QueryGOs<nsGimmick::EyeWall>("eyeWall", [this, strobeDir](nsGimmick::EyeWall* eyeWall)->bool
					{
						if (Dot(strobeDir, eyeWall->GetDirection()) <= 0.0f)
						{
							//�ڂ̕ǂ̖ڂ̈ʒu���t���b�V���͈̔͂��������ǂ����𒲂ׂ�B
							bool hitFlag = CheckHitFlash(eyeWall->GetPosition());
							if (hitFlag)
							{
								eyeWall->SetDisapperFlag(true);
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
				m_useAbility = false;
			}
		}

		/// @brief �����d���̃t���b�V�����������Ă��邩�ǂ����𒲂ׂ�B
		/// @param chackPos �������Ă��邩���ׂ����ʒu
		/// @return �������Ă������ǂ���
		bool AbilityStrobeFlash::CheckHitFlash(Vector3 checkPos)
		{		
			//�ԂɎՕ������Ȃ����𒲂ׂ�B
			Vector3 hitPos = Vector3::Zero;
			Vector3 startPos = m_flashLight->GetPosition();
			Vector3 endPos = checkPos;
			if (m_backGround->GetStageModel()->isLineHitModel(startPos, endPos, hitPos))
			{
				return false;
			}			
			
			//�����d���̌���
			Vector3 strobeDir = m_flashLight->GetFlashLightDir();
			strobeDir.Normalize();

			//���ׂ�ʒu�ւ̌���
			Vector3 toCheckPosDir = checkPos - m_flashLight->GetFlashLightPos();
			toCheckPosDir.Normalize();

			//��̃x�N�g���̓��ς���A���W�A���p�x���Z�o����B
			float angle = Dot(toCheckPosDir, strobeDir);
			angle = acos(angle);
			angle = fabsf(angle);

			//�����d���̎ˏo�p�x�Ɣ�r����
			float flashLightAngle = m_flashLight->GetFlashLightAngle();
			flashLightAngle /= 2;	//���a�̒l���~�����̂ŁA2�Ŋ���

			//���ς��ˏo�p�x���������Ȃ��
			if (angle <= flashLightAngle)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}