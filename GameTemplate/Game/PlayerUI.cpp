#include "stdafx.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerUIConstant;

		PlayerUI::~PlayerUI()
		{
			DeleteGO(m_hazySprite);
		}

		bool PlayerUI::Start()
		{
			//�_���[�W�̃X�v���C�g
			m_hazySprite = NewGO<SpriteRender>(1);
			m_hazySprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_hazySprite->SetMulColor(INI_HAZYSPRITE_COLOR);
			m_hazySprite->SetScale({ 1.0f,1.0f,1.0f });

			return true;
		}

		void PlayerUI::ExecuteUpdate()
		{
			//Hazy�X�v���C�g�̓_��
			BlinkHazySprite();

			//SAN�l��0�ɂȂ�����
			if (m_player->GetPlayerSanity()->GetSanityValue() <= 0.0f)
			{
				DyingHazySprite();
			}
		}

		void PlayerUI::SetHazySprite()
		{
			//�cHP�̔䗦����A�X�v���C�g�̐F������
			float color = (1 - m_player->GetPlayerSanity()->GetSanityValue() / nsPlayerSanityConstant::MAX_PLAYER_SANITY);
			//�F�����߂邱�ƂŁA�u���[�����N�����B
			color *= MUL_HAZYSPRITE_COLOR_VALUE;
			m_hazySprite->SetMulColor({ color, color, color, color });
		}

		//Hazy�X�v���C�g�̓_�ŏ���
		void PlayerUI::BlinkHazySprite()
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

		void PlayerUI::DyingHazySprite()
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