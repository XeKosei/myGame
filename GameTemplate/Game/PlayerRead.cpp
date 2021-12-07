#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerReadConstant;

		PlayerRead::~PlayerRead()
		{
			DeleteGO(m_blackSprite);
		}
		void PlayerRead::Init(Player* pl)
		{
			m_player = pl;

			m_blackSprite = NewGO<SpriteRender>(0);
			m_blackSprite->Init("Assets/Image/Black.DDS", 1280, 720);
			m_blackSprite->SetMulColor({ 0.0f,0.0f,0.0f,0.0f });
			m_blackOutFlag = true;

			m_messageFont = NewGO<FontRender>(0);
			m_messageFont->SetPosition({-300.0f, 200.0f});
			m_messageFont->SetScale(0.6f);
			m_messageFont->SetShadowFlag(true);
			m_messageFont->SetShadowColor({0.0f,0.0f,0.0f,1.0f});
		}
		void PlayerRead::ExecuteUpdate()
		{
			if (m_blackOutFlag == true)
			{
				if (m_blackSpriteColor.r < MAX_BLACKSPRITE_COLOR)
				{
					m_blackSpriteColor.r += ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSpriteColor.g += ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSpriteColor.b += ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSpriteColor.a += ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSprite->SetMulColor(m_blackSpriteColor);
					m_messageFont->SetText(m_message);
				}
				else
				{
					if (g_pad[0]->IsTrigger(enButtonB))
					{
						m_blackOutFlag = false;
						m_messageFont->SetText(L"");
						//SE
						SoundSource* ss = NewGO<SoundSource>(0);
						ss->Init(L"Assets/sound/ReadEnd.wav");
						ss->Play(false);
					}
				}
			}
			else
			{
				if (m_blackSpriteColor.r > 0.0f)
				{
					m_blackSpriteColor.r -= ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSpriteColor.g -= ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSpriteColor.b -= ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSpriteColor.a -= ADD_BLACKSPRITE_COLOR_SPEED;
					m_blackSprite->SetMulColor(m_blackSpriteColor);
				}
				else
				{
					m_player->SetPlayerState(Player::enState_Normal);
					m_blackOutFlag = true;
				}
			}	
		}
	}
}