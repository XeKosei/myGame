#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsAbilityMedousaEyeConstant;

		AbilityMedousaEye::~AbilityMedousaEye()
		{
			Reset();
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
						QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
							{
								//�G���X�g���{�t���b�V�����󂯂ċ���ł���Ȃ��
								if (enemy->GetEnemyState() == nsEnemy::Enemy::enState_Flinch)
								{
									//�Ή�������
									enemy->SetEnemyState(nsEnemy::Enemy::enState_Petrifaction);
									
									m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_MEDOUSAEYEFLASH_BATTERY_COST);

									Reset();
								}
								return true;
							}
						);
					}
				}
				//�X�g���{�t���b�V���̃`���[�W���������Ă�����A
				if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge())
				{
					PlayChargeSE();
					//�G�t�F�N�g�̍Đ�
					if (m_chargingEff.IsPlay() == false)
					{
						m_chargingEff.Play();
					}
					m_chargingEff.SetPosition(m_flashLight->GetModelPos());
					m_chargingEff.Update();

					//���h�D�[�T�A�C�̃`���[�W���s���B
					if (m_medousaEyeChargeCount > -20)
					{
						m_medousaEyeChargeCount--;
					}
					//�`���[�W����������
					if (m_medousaEyeChargeCount == 0)
					{
						SoundSource* ss = NewGO<SoundSource>(0);
						ss->Init(L"Assets/sound/StrobeFlashCharged.wav");
						ss->Play(false);

						PlayChargedSE();
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
			//SE
			if (m_chargeSS != nullptr)
			{
				DeleteGO(m_chargeSS);
				m_chargeSS = nullptr;
			}
			m_canPlayChargeSS = true;
			if (m_chargedSS != nullptr)
			{
				DeleteGO(m_chargedSS);
				m_chargedSS = nullptr;
			}
			m_canPlayChargedSS = true;
		}
		void AbilityMedousaEye::PlayChargeSE()
		{
			if (m_canPlayChargeSS == true)
			{
				if (m_chargeSS != nullptr)
				{
					DeleteGO(m_chargeSS);
					m_chargeSS = nullptr;
				}

				m_chargeSS = NewGO<SoundSource>(0);
				m_chargeSS->Init(L"Assets/sound/MedousaEyeCharge.wav");
				m_chargeSS->Play(false);

				m_canPlayChargeSS = false;
			}
			else
			{
				if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge() == false)
				{
					m_canPlayChargeSS = true;
				}
			}
		}

		void AbilityMedousaEye::PlayChargedSE()
		{
			if (m_canPlayChargedSS == true)
			{
				if (m_chargedSS != nullptr)
				{
					DeleteGO(m_chargedSS);
					m_chargedSS = nullptr;
				}

				m_chargedSS = NewGO<SoundSource>(0);
				m_chargedSS->Init(L"Assets/sound/MedousaEyeWaitShot.wav");
				m_chargedSS->Play(false);

				m_canPlayChargedSS = false;
			}
			else
			{
				if (g_pad[0]->IsPress(enButtonRB2) == false)
				{
					if (m_chargedSS != nullptr)
					{
						DeleteGO(m_chargedSS);
						m_chargedSS = nullptr;
					}
					m_canPlayChargedSS = true;
				}
			}
		}
	}
}