#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerSanityConstant;

		PlayerSanity::~PlayerSanity()
		{
			DeleteGO(f);
		}

		void PlayerSanity::Init(Player* pl)
		{
			m_player = pl;

			//�ő�HP��ݒ�
			m_sanityValue = MAX_PLAYER_SANITY;

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
	}
}