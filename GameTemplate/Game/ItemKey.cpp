#include "stdafx.h"
#include "ItemKey.h"
#include "ItemBase.h"
#include "PlayerInclude.h"
namespace nsHikageri
{

	namespace nsItem
	{
		ItemKey::~ItemKey()
		{
			DeleteGO(m_keyModel);
		}
		bool ItemKey::Start()
		{
			m_keyModel = NewGO<SkinModelRender>(0);
			switch (m_keyColor)
			{
			case enKeyColor_Red:
				m_keyModel->Init("Assets/modelData/RedKey.tkm");
				break;
			case enKeyColor_Blue:
				m_keyModel->Init("Assets/modelData/BlueKey.tkm");
				break;
			case enKeyColor_Green:
				m_keyModel->Init("Assets/modelData/GreenKey.tkm");
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
				case enKeyColor_Red:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_RedKey);
					break;
				case enKeyColor_Blue:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_BlueKey);
					break;
				case enKeyColor_Green:
					m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_GreenKey);
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