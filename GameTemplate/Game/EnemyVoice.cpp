#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		EnemyVoice::~EnemyVoice()
		{
			if (m_voiceSS != nullptr)
			{
				DeleteGO(m_voiceSS);
			}
		}

		void EnemyVoice::Init(Enemy* enemy)
		{
			m_enemy = enemy;
		}

		void EnemyVoice::ExecuteUpdate()
		{
			switch (m_enemy->GetEnemyState())
			{
			case Enemy::enState_SearchPlayer:
				PlayVoice();
				break;
			case Enemy::enState_Chase:
				PlayVoice();
				break;
			case Enemy::enState_Attack:
				PlayVoice();
				break;
			case Enemy::enState_Scream:
				PlayVoice();
				break;
			case Enemy::enState_Flinch:
				PlayVoice();
				break;
			case Enemy::enState_Petrifaction:
				PetrifactionVoice();
				return;
				break;
			case Enemy::enState_Suffer:
				PlayVoice();
				break;
			case Enemy::enState_Vigilant:
				
				break;
			default:
				break;
			}

			if (m_voiceSS != nullptr)
			{
				//プレイヤーとの距離から、音量を設定
				float dis = (m_enemy->GetEnemyMove()->GetPosition() - m_enemy->GetPlayer()->GetPlayerMove()->GetPosition()).Length();
				float volume = max(0.01f, 1.0f - dis * 0.0003f);
				m_voiceSS->SetVolume(volume);
			}
		}

		void EnemyVoice::PlayVoice()
		{
			if (m_oldEnemyState != m_enemy->GetEnemyState())
			{
				m_canPlayVoiceSS = true;
			}
			m_oldEnemyState = m_enemy->GetEnemyState();

			if (m_canPlayVoiceSS)
			{
				if (m_voiceSS != nullptr)
				{
					DeleteGO(m_voiceSS);
					m_voiceSS = nullptr;
				}

				m_voiceSS = NewGO<SoundSource>(0);

				switch (m_enemy->GetEnemyState())
				{
				case Enemy::enState_SearchPlayer:
					if (m_enemy->GetEnemyMove()->GetSlowMoveFlag())
						m_voiceSS->Init(L"Assets/sound/EnemySlowMove.wav");
					else
						m_voiceSS->Init(L"Assets/sound/EnemyDefault.wav");
					break;
				case Enemy::enState_Chase:
					if (m_enemy->GetEnemyMove()->GetSlowMoveFlag())
						m_voiceSS->Init(L"Assets/sound/EnemySlowMove.wav");
					else
						m_voiceSS->Init(L"Assets/sound/EnemyChase.wav");
					break;
				case Enemy::enState_Attack:
					m_voiceSS->Init(L"Assets/sound/EnemyAttack.wav");
					break;
				case Enemy::enState_Scream:
					m_voiceSS->Init(L"Assets/sound/EnemyScream.wav");
					break;
				case Enemy::enState_Flinch:
					m_voiceSS->Init(L"Assets/sound/EnemyFlinch.wav");
					break;
				case Enemy::enState_Petrifaction:

					break;
				case Enemy::enState_Suffer:
					m_voiceSS->Init(L"Assets/sound/EnemySuffer.wav");
					break;
				case Enemy::enState_Vigilant:
					m_voiceSS->Init(L"Assets/sound/EnemyDefault.wav");
					break;
				default:
					m_voiceSS->Init(L"Assets/sound/EnemyDefault.wav");
					break;
				}
				
				m_voiceSS->Play(true);
				m_canPlayVoiceSS = false;
			}
		}

		void EnemyVoice::PetrifactionVoice()
		{
			if (m_oldEnemyState != m_enemy->GetEnemyState())
			{
				m_canPlayVoiceSS = true;
			}
			m_oldEnemyState = m_enemy->GetEnemyState();

			if (m_canPlayVoiceSS)
			{
				if (m_voiceSS != nullptr)
				{
					DeleteGO(m_voiceSS);
					m_voiceSS = nullptr;
				}

				m_voiceSS = NewGO<SoundSource>(0);
				m_voiceSS->Init(L"Assets/sound/EnemyFlinch.wav");
				m_voiceSS->Play(false);
				m_canPlayVoiceSS = false;
			}
		}
	}
}