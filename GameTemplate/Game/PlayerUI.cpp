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
			//ダメージのスプライト
			m_hazySprite = NewGO<SpriteRender>(1);
			m_hazySprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_hazySprite->SetMulColor(INI_HAZYSPRITE_COLOR);
			m_hazySprite->SetScale({ 1.0f,1.0f,1.0f });

			return true;
		}

		void PlayerUI::ExecuteUpdate()
		{
			//Hazyスプライトの点滅
			BlinkHazySprite();

			//SAN値が0になったら
			if (m_player->GetPlayerSanity()->GetSanityValue() <= 0.0f)
			{
				DyingHazySprite();
			}
		}

		void PlayerUI::SetHazySprite()
		{
			//残HPの比率から、スプライトの色を決定
			float color = (1 - m_player->GetPlayerSanity()->GetSanityValue() / nsPlayerSanityConstant::MAX_PLAYER_SANITY);
			//色を強めることで、ブルームを起こす。
			color *= MUL_HAZYSPRITE_COLOR_VALUE;
			m_hazySprite->SetMulColor({ color, color, color, color });
		}

		//Hazyスプライトの点滅処理
		void PlayerUI::BlinkHazySprite()
		{
			//スプライトの点滅
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

			//点滅分のa値を加算
			m_hazyColor = m_hazySprite->GetMulColor();
			m_hazyColor.a += m_addAlpha;
			m_hazySprite->SetMulColor(m_hazyColor);
		}

		void PlayerUI::DyingHazySprite()
		{
			//スプライトを強く表示する。
			if (m_addAlpha <= DYING_MAX_ADD_ALPHA)
				m_addAlpha += DYING_ADD_ALPHA_SPEED;

			m_hazyColor = m_hazySprite->GetMulColor();
			m_hazyColor.a += m_addAlpha;
			m_hazySprite->SetMulColor(m_hazyColor);
		}
	}
}