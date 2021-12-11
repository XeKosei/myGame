#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerSanityConstant;

		PlayerSanity::~PlayerSanity()
		{
			DeleteGO(m_bloodSprite);
			DeleteGO(f);
		}

		void PlayerSanity::Init(Player* pl)
		{
			m_player = pl;

			//�ő�HP��ݒ�
			m_sanityValue = MAX_PLAYER_SANITY;

			m_bloodSprite = NewGO<SpriteRender>(10);
			m_bloodSprite->Init("Assets/image/BloodSprite.DDS",1000, 1000);
			m_bloodSprite->SetMulColor(m_bloodSpriteColor);

			//�f�o�b�O�p
			f = NewGO<FontRender>(3);
			f->SetText(L"SAN�l:" + std::to_wstring(m_sanityValue));
			f->SetPosition({300.0f, 200.0f});
			f->SetScale(0.0f);
		}

		void PlayerSanity::ExecuteUpdate()
		{
			//���S�ł��Ȃ��󋵂Ȃ�΁ASAN�l����
			if (m_reliefFlag == false)
			{
				Damage(DARKNESS_SANITY_DAMAGE_SPEED);
			}
			m_reliefFlag = false;

			//�C���^�[�o�����J�E���g
			if (m_damageIntervalCount != 0)
			{
				m_damageIntervalCount--;
			}	
		
			//�S��
			Heartbeat();
			//���̃X�v���C�g
			BloodSprite();
		}

		/// @brief �v���C���[��SAN�l���w�肵���l�������炷�B
		/// @param damageNum �^����_���[�W
		void PlayerSanity::Damage(float damageNum)
		{
			if (m_player->GetPlayerState() != Player::enState_Dead)
			{
				//�C���^�[�o���łȂ����
				//if (m_damageIntervalCount == 0)
				//{
				m_sanityValue -= damageNum;	

				//�̗͂�0�ɂȂ�����
				if (m_sanityValue <= 0)
				{
					m_sanityValue = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}

				//�X�v���C�g��ݒ�
				m_player->GetPlayerUI()->SetHazySprite();

				//�_���[�W���傫�����
				if (damageNum >= 1.0f)
				{
					m_bloodSpriteFlag = true;
				}

				//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̃C���^�[�o����ݒ�B
				m_damageIntervalCount = DAMAGE_INTERVAL;
				//}

				//HP�\��(��)
				f->SetText(L"SAN�l:" + std::to_wstring(m_sanityValue));
			}
		}

		void PlayerSanity::Recovery(int recoveryNum)
		{
			if (m_player->GetPlayerState() == Player::enState_Normal ||
				m_player->GetPlayerState() == Player::enState_Invincible)
			{
				m_sanityValue += recoveryNum;	

				//�̗͂��ő�ɂȂ�����
				if (m_sanityValue >= MAX_PLAYER_SANITY)
				{
					m_sanityValue = MAX_PLAYER_SANITY;
				}

				//�X�v���C�g��ݒ�
				m_player->GetPlayerUI()->SetHazySprite();

				//HP�\��(��)
				f->SetText(L"SAN�l:" + std::to_wstring(m_sanityValue));
			}
		}

		void PlayerSanity::Heartbeat()
		{
			//�̗͂�������؂�����
			if (m_sanityValue <= MAX_PLAYER_SANITY * 0.5)
			{
				m_heartbeatIntervalCount--;

				if (m_heartbeatIntervalCount < 0)
				{
					SoundSource* ss = NewGO<SoundSource>(0);

					//�c��SAN�l�ɉ����āASE��SE�̊Ԋu��ω�������B
					if (m_sanityValue <= MAX_PLAYER_SANITY * 0.1)
					{
						ss->Init(L"Assets/sound/Heartbeat4.wav");
						m_heartbeatInterval = 20;
					}
					else if (m_sanityValue <= MAX_PLAYER_SANITY * 0.2)
					{
						ss->Init(L"Assets/sound/Heartbeat3.wav");
						m_heartbeatInterval = 30;
					}
					else if (m_sanityValue <= MAX_PLAYER_SANITY * 0.3)
					{
						ss->Init(L"Assets/sound/Heartbeat2.wav");
						m_heartbeatInterval = 40;
					}
					else if (m_sanityValue <= MAX_PLAYER_SANITY * 0.4)
					{
						ss->Init(L"Assets/sound/Heartbeat1.wav");
						m_heartbeatInterval = 50;
					}				
					else
					{
						ss->Init(L"Assets/sound/Heartbeat0.wav");
						m_heartbeatInterval = 60;
					}

					ss->Play(false);

					m_heartbeatIntervalCount = m_heartbeatInterval;
				}
			}
			else
			{
				m_heartbeatIntervalCount = 0;
				m_heartbeatInterval = 60;
			}
		}

		void PlayerSanity::BloodSprite()
		{
			if (m_bloodSpriteFlag)
			{
				m_bloodSpriteColor = { MAX_BLOODSPRITE_COLOR,MAX_BLOODSPRITE_COLOR,MAX_BLOODSPRITE_COLOR,MAX_BLOODSPRITE_COLOR };
				m_bloodSpriteFlag = false;
			}

			m_bloodSpriteColor.r -= BLOODSPRITE_DEC_SPEED;
			m_bloodSpriteColor.g -= BLOODSPRITE_DEC_SPEED;
			m_bloodSpriteColor.b -= BLOODSPRITE_DEC_SPEED;
			m_bloodSpriteColor.a -= BLOODSPRITE_DEC_SPEED;


			if (m_bloodSpriteColor.x <= 0.0f)
			{
				m_bloodSpriteColor = { 0.0f,0.0f, 0.0f, 0.0f };
			}
			m_bloodSprite->SetMulColor(m_bloodSpriteColor);
		}
	}
}