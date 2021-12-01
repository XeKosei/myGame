#include "stdafx.h"
#include "ItemInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	using namespace nsGimmick;
	namespace nsItem
	{
		using namespace nsItemConstant;

		ItemBattery::~ItemBattery()
		{
			if (m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Battery
				&& m_player->GetPlayerTarget()->GetTargetBattery() == this)
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_None);

			DeleteGO(m_batteryModel);
		}
		bool ItemBattery::Start()
		{
			m_batteryModel = NewGO<SkinModelRender>(0);

			m_batteryModel->Init("Assets/modelData/Battery.tkm");
			m_batteryModel->SetPosition(m_position);

			return true;
		}

		void ItemBattery::Update()
		{
			Vector3 dis = m_position - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、こちらの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Battery);
				m_player->GetPlayerTarget()->SetTargetBattery(this);
			}

			//プレイヤーのターゲットがこのアイテムで、Aボタンが押されたら、入手
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Battery
				&& m_player->GetPlayerTarget()->GetTargetBattery() == this)
			{
				m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_Battery);
				DeleteGO(this);
			}
		}
	}
}