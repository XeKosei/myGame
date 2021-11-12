#include "stdafx.h"
#include "ItemKey.h"
#include "ItemBase.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	using namespace nsGimmick;
	namespace nsItem
	{
		ItemKey::~ItemKey()
		{
			if (m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Key
				&& m_player->GetPlayerTarget()->GetTargetKey() == this)
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_None);

			DeleteGO(m_keyModel);
		}
		bool ItemKey::Start()
		{
			m_keyModel = NewGO<SkinModelRender>(0);
			switch (m_keyColor)
			{
			case Door::enDoorColor_Red:
				m_keyModel->Init("Assets/modelData/RedKey.tkm");
				break;
			case Door::enDoorColor_Blue:
				m_keyModel->Init("Assets/modelData/BlueKey.tkm");
				break;
			case Door::enDoorColor_Green:
				m_keyModel->Init("Assets/modelData/GreenKey.tkm");
				break;
			case Door::enDoorColor_Yellow:
				m_keyModel->Init("Assets/modelData/YellowKey.tkm");
				break;
			case Door::enDoorColor_Purple:
				m_keyModel->Init("Assets/modelData/PurpleKey.tkm");
				break;
			case Door::enDoorColor_White:
				m_keyModel->Init("Assets/modelData/WhiteKey.tkm");
				break;
			default:
				m_keyModel->Init("Assets/modelData/Key.tkm");
				break;
			}
			m_keyModel->SetPosition(m_position);

			return true;
		}

		void ItemKey::Update()
		{
			Vector3 dis = m_position - m_player->GetPlayerMove()->GetPosition();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、こちらの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Key);
				m_player->GetPlayerTarget()->SetTargetKey(this);
			}

			//プレイヤーのターゲットがこの鍵で、Aボタンが押されたら、入手
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Key
				&& m_player->GetPlayerTarget()->GetTargetKey() == this)
			{
				switch (m_keyColor)
				{
				case Door::enDoorColor_Red:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_RedKey);
					break;
				case Door::enDoorColor_Blue:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_BlueKey);
					break;
				case Door::enDoorColor_Green:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_GreenKey);
					break;
				case Door::enDoorColor_Yellow:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_YellowKey);
					break;
				case Door::enDoorColor_Purple:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_PurpleKey);
					break;
				case Door::enDoorColor_White:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_LastKey);
					break;
				default:
					return;
					break;
				}	
				DeleteGO(this);
			}
		}
	}
}