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

			//���̃X�v���C�g
			m_bloodSprite = NewGO<SpriteRender>(1);
			m_bloodSprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_bloodSprite->SetMulColor(INI_BLOODSPRITE_COLOR);
			m_bloodSprite->SetScale({ 2.0f,2.0f,2.0f });


			//�f�o�b�O�p
			f = NewGO<FontRender>(0);
			//f->SetText(std::to_wstring(m_HP));

			//�Q�[���I�[�o�[�p�t�H���g(��)
			m_gameOverFont = NewGO<FontRender>(2);
			m_gameOverFont->SetText(L"GAME OVER");
			m_gameOverFont->SetScale(3.0f);
			m_gameOverFont->SetPosition({ -300.0f, 50.0f });
			m_gameOverFont->SetColor({0.0f,0.0f,0.0f,0.0f});
			m_gameOverFont->SetShadowFlag(true);
			m_gameOverFont->SetShadowOffset(3.0f);
			m_gameOverFont->SetShadowColor({ 0.0f,0.0f,0.0f,0.0f });

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
				BloodSpriteBlink();
			}

			if (m_HP <= 0)
			{
				GameOver();
			}
			
			if (g_pad[0]->IsTrigger(enButtonX))
			{
				m_HP = 100;
			}

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				Damage(5);
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

				//���̃X�v���C�g��ݒ�
				SetBloodSprite();

				//�̗͂�0�ɂȂ�����
				if (m_HP <= 0)
				{
					m_HP = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}
				//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̃C���^�[�o����ݒ�B
				m_damageIntervalCount = DAMAGE_INTERVAL;
				//}

				//HP�\��(��)
				//f->SetText(std::to_wstring(m_HP));
			}
		}

		void PlayerHP::SetBloodSprite()
		{
			//�v���C���[�̎c�̗͂ɂ���Č��̃X�v���C�g��ω�������B
			if (m_HP > BIG_DAMAGE_LINE)
			{
				//�X�v���C�g�̐F�͒ʏ�B
				m_bloodSprite->SetMulColor({ DAMAGED_BLOODSPRITE_COLOR });
			}
			else
			{
				//�cHP�̔䗦����A�X�v���C�g�̐F������
				float bloodColor = (1 - m_HP / MAX_PLAYER_HP);
				//R�����F�����߂邱�ƂŁA�u���[�����N�����B�B
				m_bloodSprite->SetMulColor({ bloodColor, bloodColor, bloodColor, 1.0f });
			}

			//�X�v���C�g�̑傫����ݒ肷��(1�`2�͈̔�)
			float bloodScale = 1 + m_HP / MAX_PLAYER_HP;
			m_bloodSprite->SetScale({ bloodScale,bloodScale,bloodScale });
		}

		//��ʒ[�̌��̃X�v���C�g�̏���
		void PlayerHP::BloodSpriteBlink()
		{
			//�X�v���C�g�̓_��
			if (m_addRedFlag == true)
			{
				m_addAlpha += ADD_ALPHA_SPEED;
				if (m_addAlpha >= MAX_ADD_ALPHA)
				{
					m_addRedFlag = false;
				}
			}
			else if (m_addRedFlag == false)
			{
				m_addAlpha -= ADD_ALPHA_SPEED;
				if (m_addAlpha <= MIN_ADD_ALPHA)
				{
					m_addRedFlag = true;
				}
			}

			//�_�ŕ���a�l�����Z
			m_bloodColor = m_bloodSprite->GetMulColor();
			m_bloodColor.a += m_addAlpha;
			m_bloodSprite->SetMulColor(m_bloodColor);
		}

		void PlayerHP::GameOver()
		{
			//���񂾂Ƃ��̉��o
			if (m_player->GetPlayerState() == Player::enState_Dead)
			{
				m_addAlpha += MAX_ADD_ALPHA * 1;
			}

			if (m_gameOverMoveCount > 0)
			{
				m_gameOverMoveCount--;
			}

			if (m_gameOverMoveCount <= 100 && m_gameOverMoveCount > 0)
			{
				m_gameOverFontColor.r += 0.01f;
				m_gameOverFontColor.a += 0.01f;
				m_gameOverFont->SetColor(m_gameOverFontColor);
				m_gameOverFontShadowColor.a += 0.01f;
				m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
			}
		}

	}
}