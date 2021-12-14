#include "stdafx.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerPouchConstant;

		PlayerPouch::~PlayerPouch()
		{
			
		}

		void PlayerPouch::Init(Player* pl)
		{
			m_player = pl;
		}

		void PlayerPouch::ExecuteUpdate()
		{
			SelectItem();
		
			UseItem();

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
				case enItem_LastKey:
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
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
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
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
			}
		}

		//アイテムの追加
		void PlayerPouch::AddItem(EnPlayerItems item)
		{ 
			m_choseItem = item;
			//アイテムの数を増やす
			m_haveItemNum[m_choseItem]++;
			//UI更新
			m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
		}

		//電池を使用したときの処理
		void PlayerPouch::UseBattery()
		{
			if (g_pad[0]->IsTrigger(enButtonX))
			{
				//アイテムの数を1減らす
				m_haveItemNum[m_choseItem]--;
				//UIの更新
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
				//バッテリー回復
				m_player->GetFlashLight()->GetFlashLightBattery()->SetBatteryLevel(nsFlashLight::nsFlashLightBatteryConstant::MAX_BATTERY_LEVEL);
				//SE
				UseItemSE(enUseItemSounds_Battery);
			}
		}

		//精神安定剤を使用したとき
		void PlayerPouch::UseTranquilizar()
		{
			if (g_pad[0]->IsTrigger(enButtonX))
			{
				//アイテムの数を1減らす
				m_haveItemNum[m_choseItem]--;
				//UIの更新
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
				//SAN値回復
				m_player->GetPlayerSanity()->Recovery(TRANQUILIZER_RECOVERY_NUM);
				//SE
				UseItemSE(enUseItemSounds_Tranquilizer);
			}
		}

		void PlayerPouch::UseKey()
		{
			if (g_pad[0]->IsTrigger(enButtonX) || g_pad[0]->IsTrigger(enButtonA) )
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
				case enItem_LastKey:
					if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
					{
						if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_White)
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
					//UI更新
					m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
					//鍵を解除
					m_player->GetPlayerTarget()->GetTargetDoor()->SetUnlockFlag(true);
					//SE
					UseItemSE(enUseItemSounds_Key);
				}
			}
		}

		void PlayerPouch::UseItemSE(EnUseItemSounds soundKind)
		{
			if (m_useItemSS != nullptr)
			{
				DeleteGO(m_useItemSS);
				m_useItemSS = nullptr;
			}

			switch (soundKind)
			{
			case enUseItemSounds_Battery:
				m_useItemSS = NewGO<SoundSource>(0);
				m_useItemSS->Init(L"Assets/sound/UseItemBattery.wav");
				m_useItemSS->Play(false);
				break;
			case enUseItemSounds_Tranquilizer:
				m_useItemSS = NewGO<SoundSource>(0);
				m_useItemSS->Init(L"Assets/sound/UseItemTranquilizer.wav");
				m_useItemSS->Play(false);
				break;
			case enUseItemSounds_Key:
				m_useItemSS = NewGO<SoundSource>(0);
				m_useItemSS->Init(L"Assets/sound/UseItemKey.wav");
				m_useItemSS->Play(false);
				break;
			}
		}
	}
}