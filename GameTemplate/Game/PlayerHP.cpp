#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerHPConstant;

		bool PlayerHP::Start()
		{
			//�ő�HP��ݒ�
			m_HP = MAX_PLAYER_HP;
			m_bloodSprite = NewGO<SpriteRender>(1);
			m_bloodSprite->Init("Assets/Image/BloodBlur.DDS", 1280, 720);
			m_bloodSprite->SetMulColor(INI_BLOODSPRITE_COLOR);
			return true;
		}

		void PlayerHP::ExecuteUpdate()
		{
			//�C���^�[�o�����J�E���g
			if (m_damageIntervalCount != 0)
			{
				m_damageIntervalCount--;
			}

			//HP��������؂�����
			if (m_HP <= MAX_PLAYER_HP / 2)
			{
				BloodSprite();
			}
					
		}

		/// @brief �v���C���[�̃_���[�W���w�肵���l�������炷�B
		/// @param damageNum �^����_���[�W
		void PlayerHP::Damage(int damageNum)
		{
			if (m_player->GetPlayerState() != Player::enState_Dead)
			{
				//�C���^�[�o���łȂ����
				//if (m_damageIntervalCount == 0)
				//{
				m_HP -= damageNum;

				//�v���C���[�̗̑͂ɍ��킹�āA�X�v���C�g��r�l��a�l���グ��B
				float rgbColor = (1 - m_HP / MAX_PLAYER_HP) * 1000.0f;
				float a = (1 - m_HP / MAX_PLAYER_HP) / 80.0f;
				m_bloodSprite->SetMulColor( {rgbColor, rgbColor/100, rgbColor/100, a });

				//�̗͂�0�ɂȂ�����
				if (m_HP <= 0)
				{
					m_HP = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}
				//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̃C���^�[�o����ݒ�B
				m_damageIntervalCount = DAMAGE_INTERVAL;
				//}
			}
		}

		
		//��ʒ[�̌��̃X�v���C�g�̏���
		void PlayerHP::BloodSprite()
		{
			//���񂾂Ƃ��̉��o
			if (m_player->GetPlayerState() == Player::enState_Dead)
			{
				m_addRed += MAX_ADD_RED * 1;
			}
			//�X�v���C�g�̓_��
			else if (m_addRedFlag == true)
			{
				m_addRed += ADD_RED_SPEED;
				if (m_addRed >= MAX_ADD_RED)
				{
					m_addRedFlag = false;
				}
			}
			else if (m_addRedFlag == false)
			{
				m_addRed -= ADD_RED_SPEED;
				if (m_addRed <= MIN_ADD_RED)
				{
					m_addRedFlag = true;
				}
			}

			//�_�ŕ��̐ԐF�����Z
			m_bloodColor = m_bloodSprite->GetMulColor();
			m_bloodColor.a += m_addRed;
			m_bloodSprite->SetMulColor(m_bloodColor);
		}
	}
}