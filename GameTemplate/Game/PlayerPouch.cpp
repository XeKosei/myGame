#include "stdafx.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerPouchConstant;

		bool PlayerPouch::Start()
		{
			//画面表示
			m_itemFont = NewGO<FontRender>(2);
			m_itemFont->SetText(ITEM_NAME[m_choseItem]);
			m_itemFont->SetScale(1.0f);
			m_itemFont->SetPosition({ -600.0f, -200.0f });
			m_itemFont->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			m_itemFont->SetShadowFlag(true);
			m_itemFont->SetShadowOffset(1.0f);
			m_itemFont->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

			m_itemNumFont = NewGO<FontRender>(2);
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			m_itemNumFont->SetScale(1.0f);
			m_itemNumFont->SetPosition({ -500.0f, -250.0f });
			m_itemNumFont->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			m_itemNumFont->SetShadowFlag(true);
			m_itemNumFont->SetShadowOffset(1.0f);
			m_itemNumFont->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

			/*m_itemUsedFont = NewGO<FontRender>(2);
			m_itemUsedFont->SetText(L"使用できない。");
			m_itemUsedFont->SetScale(1.0f);
			m_itemUsedFont->SetPosition({ -200.0f, -225.0f });
			m_itemUsedFontColor = {1.0f,1.0f,1.0f,0.0f};
			m_itemUsedFont->SetColor(m_itemUsedFontColor);
			m_itemUsedFont->SetShadowFlag(true);
			m_itemUsedFont->SetShadowOffset(1.0f);
			m_itemUsedFont->SetShadowColor({ 0.0f,0.0f,0.0f,0.0f });
			m_itemUsedFontCount = 300;*/

			return true;
		}

		void PlayerPouch::ExecuteUpdate()
		{
			SelectItem();

			if (g_pad[0]->IsTrigger(enButtonX))
			{
				UseItem();
			}
		}

		void PlayerPouch::UseItem()
		{
			//アイテムを1個以上持っているならば
			if (m_haveItemNum[m_choseItem] > 0)
			{
				switch (m_choseItem)
				{
				case enItem_Battery:
					UseBattery();
					break;
				case enItem_Tranquilizer:
					UseTranquilizar();
					break;
				case enItem_RedKey:
					UseKey();
					break;
				case enItem_BlueKey:
					UseKey();
					break;
				case enItem_GreenKey:
					UseKey();
					break;
				case enItem_YellowKey:
					UseKey();
					break;
				case enItem_PurpleKey:
					UseKey();
					break;
				default:
					break;
				}
			}
		}

		//アイテムを選択する
		void PlayerPouch::SelectItem() 
		{
			//右ボタンを押すと
			if (g_pad[0]->IsTrigger(enButtonRight))
			{
				for (int i = 0; i < enItem_num; i++)
				{
					m_choseItem++;
					//アイテムの番号が最大になったら、番号を0に戻す。
					if (m_choseItem >= enItem_num)
					{
						m_choseItem = 0;
					}
					//所持していないアイテムは飛ばす
					if (m_haveItemNum[m_choseItem] > 0)
					{
						break;
					}
				}
		
				//テキストを設定
				m_itemFont->SetText(ITEM_NAME[m_choseItem]);
				m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));		
			}
			//左ボタンを押すと
			if (g_pad[0]->IsTrigger(enButtonLeft))
			{
				for (int i = 0; i < enItem_num; i++)
				{
					m_choseItem--;
					//アイテムの番号が0以下になったら、番号を最大にする。
					if (m_choseItem < 0)
					{
						m_choseItem = enItem_num - 1;
					}

					//所持していないアイテムは飛ばす
					if (m_haveItemNum[m_choseItem] > 0)
					{
						break;
					}
				}

				//テキストを設定
				m_itemFont->SetText(ITEM_NAME[m_choseItem]);
				m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));		
			}
		}
		//電池を使用したときの処理
		void PlayerPouch::UseBattery()
		{
			//アイテムの数を1減らす
			m_haveItemNum[m_choseItem]--;
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			m_player->GetFlashLight()->GetFlashLightBattery()->SetBatteryLevel(nsFlashLight::nsFlashLightBatteryConstant::MAX_BATTERY_LEVEL);
		}

		//精神安定剤を使用したとき
		void PlayerPouch::UseTranquilizar()
		{
			//アイテムの数を1減らす
			m_haveItemNum[m_choseItem]--;
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			m_player->GetPlayerSanity()->Recovery(TRANQUILIZER_RECOVERY_NUM);
		}

		void PlayerPouch::UseKey()
		{
			//ドアのカギを開けるかどうかのフラグ
			bool unlockFlag = false;

			//鍵の色とドアの色が一致しているかを管理
			switch (m_choseItem)
			{		
			case enItem_RedKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Red)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_BlueKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Blue)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_GreenKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Green)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_YellowKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Yellow)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_PurpleKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Purple)
					{
						unlockFlag = true;
					}
				}
				break;
			default:
				break;
			}

			if (unlockFlag)
			{
				//アイテムの数を1減らす
				m_haveItemNum[m_choseItem]--;
				m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
				//鍵を解除
				m_player->GetPlayerTarget()->GetTargetDoor()->SetUnlockFlag(true);
			}
		}

		//void PlayerPouch::CannotUse()
		//{
		//	if (m_itemUsedFontCount == 300)
		//	{
		//		m_itemUsedFontColor.a = 1.0f;
		//	}
		//	if (m_itemUsedFontCount > 0)
		//	{
		//		m_itemUsedFontCount--;
		//	}

		//	if (m_itemUsedFontCount <= 100 && m_itemUsedFontCount > 0)
		//	{
		//		m_itemUsedFontColor.a -= 0.01f;
		//		m_itemUsedFont->SetColor(m_itemUsedFontColor);
		//		//m_gameOverFontShadowColor.a += 0.01f;
		//		//m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
		//	}
		//}
	}
}