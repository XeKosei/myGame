#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerSanityConstant;

		PlayerSanity::~PlayerSanity()
		{
			DeleteGO(m_hazySprite);
			DeleteGO(f);
		}

		bool PlayerSanity::Start()
		{
			//�ő�HP��ݒ�
			m_sanityValue = MAX_PLAYER_SANITY;

			//�_���[�W�̃X�v���C�g
			m_hazySprite = NewGO<SpriteRender>(1);
			m_hazySprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_hazySprite->SetMulColor(INI_HAZYSPRITE_COLOR);
			m_hazySprite->SetScale({ 1.0f,1.0f,1.0f });

			//�f�o�b�O�p
			f = NewGO<FontRender>(3);
			f->SetText(L"SAN�l:" + std::to_wstring(m_sanityValue));
			f->SetPosition({300.0f, 200.0f});

			return true;
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

			//SAN�l��0�ɂȂ�����
			if (m_sanityValue <= 0)
			{
				DYING();
			}

			//SAN�l��������؂�����
			if (m_sanityValue <= MAX_PLAYER_SANITY / 2)
			{
				HazySpriteBlink();
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
				SetHazySprite();

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
				SetHazySprite();

				//HP�\��(��)
				f->SetText(L"SAN�l:" + std::to_wstring(m_sanityValue));
			}
		}

		void PlayerSanity::SetHazySprite()
		{	
			//�cHP�̔䗦����A�X�v���C�g�̐F������
			float color = (1 - m_sanityValue / MAX_PLAYER_SANITY) * 1.5f;
			//R�����F�����߂邱�ƂŁA�u���[�����N�����B�B
			m_hazySprite->SetMulColor({ color, color, color, color });
			
			//�X�v���C�g�̑傫����ݒ肷��(1�`2�͈̔�)
			//float scale = 1 + m_sanityValue / MAX_PLAYER_SANITY;
			//m_hazySprite->SetScale({ scale,scale,scale });
		}

		//Hazy�X�v���C�g�̓_�ŏ���
		void PlayerSanity::HazySpriteBlink()
		{
			//�X�v���C�g�̓_��
			if (m_addAlphaFlag == true)
			{
				m_addAlpha += ADD_ALPHA_SPEED;
				if (m_addAlpha >= MAX_ADD_ALPHA)
				{
					m_addAlphaFlag = false;
				}
			}
			else if (m_addAlphaFlag == false)
			{
				m_addAlpha -= ADD_ALPHA_SPEED;
				if (m_addAlpha <= MIN_ADD_ALPHA)
				{
					m_addAlphaFlag = true;
				}
			}			

			//�_�ŕ���a�l�����Z
			m_hazyColor = m_hazySprite->GetMulColor();
			m_hazyColor.a += m_addAlpha;
			m_hazySprite->SetMulColor(m_hazyColor);
		}

		void PlayerSanity::DYING()
		{
			//�X�v���C�g�������\������B
			if (m_addAlpha <= DYING_MAX_ADD_ALPHA)
				m_addAlpha += DYING_ADD_ALPHA_SPEED;
			
			m_hazyColor = m_hazySprite->GetMulColor();
			m_hazyColor.a += m_addAlpha;
			m_hazySprite->SetMulColor(m_hazyColor);
		}
	}
}