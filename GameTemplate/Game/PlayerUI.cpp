#include "stdafx.h"
#include "PlayerInclude.h"
#include "FlashLightConstant.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerUIConstant;

		PlayerUI::~PlayerUI()
		{
			DeleteGO(m_hazySprite);
		
			DeleteGO(m_itemFont);
			DeleteGO(m_itemNumFont);

			for (int no = 0; no < enBatteryDispTypes_num; no++)
			{
				DeleteGO(m_batterySprite[no]);
			}
		}

		bool PlayerUI::Start()
		{
			//ダメージのスプライト
			m_hazySprite = NewGO<SpriteRender>(1);
			m_hazySprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_hazySprite->SetMulColor(INI_HAZYSPRITE_COLOR);
			m_hazySprite->SetScale({ 1.0f,1.0f,1.0f });

			//ポーチアイテムの画面表示
			m_itemFont = NewGO<FontRender>(2);
			m_itemFont->SetText(L"");
			m_itemFont->SetScale(1.0f);
			m_itemFont->SetPosition(INI_ITEMFONT_POS);
			m_itemFont->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			m_itemFont->SetShadowFlag(true);
			m_itemFont->SetShadowOffset(1.0f);
			m_itemFont->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

			m_itemNumFont = NewGO<FontRender>(2);
			m_itemNumFont->SetText(L"");
			m_itemNumFont->SetScale(1.0f);
			m_itemNumFont->SetPosition(INI_ITEMNUMFONT_POS);
			m_itemNumFont->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			m_itemNumFont->SetShadowFlag(true);
			m_itemNumFont->SetShadowOffset(1.0f);
			m_itemNumFont->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

			//バッテリー表示
			for (int no = 0; no < enBatteryDispTypes_num; no++)
			{
				m_batterySprite[no] = NewGO<SpriteRender>(2);
				m_batterySprite[no]->Init(BATTERYSPRITE_FILEPATH[no],500,500);
				m_batterySprite[no]->SetPosition(INI_BATTERYSPRITE_POS);
				m_batterySprite[no]->SetScale({ 0.0f, 0.0f, 0.0f });
			}

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

		//ポーチアイテムの表示
		void PlayerUI::SetItemFont(int itemKind, int itemNum)
		{
			m_itemFont->SetText(ITEM_NAME[itemKind]);
			m_itemNumFont->SetText(std::to_wstring(itemNum));
		}

		//バッテリー残量の設定
		void PlayerUI::SetBatterySprite(float batteryLevel)
		{
			EnBatteryDispTypes type;
			//バッテリー残量に合わせて、表示を変更する。
			if (batteryLevel > BATTERYSPRITE_CHANGE_LINE[enBatteryDispTypes_moreThan75])
			{
				type = enBatteryDispTypes_moreThan75;
			}
			else if (batteryLevel > BATTERYSPRITE_CHANGE_LINE[enBatteryDispTypes_moreThan50])
			{
				type = enBatteryDispTypes_moreThan50;
			}
			else if (batteryLevel > BATTERYSPRITE_CHANGE_LINE[enBatteryDispTypes_moreThan25])
			{
				type = enBatteryDispTypes_moreThan25;
			}
			else if(batteryLevel > BATTERYSPRITE_CHANGE_LINE[enBatteryDispTypes_moreThan00])
			{
				type = enBatteryDispTypes_moreThan00;
			}
			else
			{
				type = enBatteryDispTypes_runOut;
			}

			//バッテリーの表示を変える
			if (type != m_batteryDispType)
			{
				m_batterySprite[m_batteryDispType]->SetScale({ 0.0f, 0.0f, 0.0f });
				m_batteryDispType = type;
				m_batterySprite[m_batteryDispType]->SetScale(INI_BATTERYSPRITE_SCALE);
			}
		}
	}
}