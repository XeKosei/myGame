#include "stdafx.h"
#include "ItemInclude.h"
#include "ItemBase.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	using namespace nsGimmick;

	namespace nsItem
	{
		using namespace nsItemConstant;

		ItemTranquilizer::~ItemTranquilizer()
		{
			if (m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Tranquilizer
				&& m_player->GetPlayerTarget()->GetTargetTranquilizer() == this)
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_None);

			DeleteGO(m_tranquilizerModel);
		}
		bool ItemTranquilizer::Start()
		{
			m_tranquilizerModel = NewGO<SkinModelRender>(0);
			
			m_tranquilizerModel->Init("Assets/modelData/Medicine.tkm");
			m_tranquilizerModel->SetPosition(m_position);

			return true;
		}

		void ItemTranquilizer::Update()
		{
			Vector3 dis = m_position - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、こちらの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Tranquilizer);
				m_player->GetPlayerTarget()->SetTargetTranquilizer(this);
			}

			//プレイヤーのターゲットがこのアイテムで、Aボタンが押されたら、入手
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Tranquilizer
				&& m_player->GetPlayerTarget()->GetTargetTranquilizer() == this)
			{
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/GetItemTranquilizer.wav");
				ss->Play(false);
				m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_Tranquilizer);		
				DeleteGO(this);
			}
		}
	}
}