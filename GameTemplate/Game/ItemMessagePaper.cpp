#include "stdafx.h"
#include "ItemInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsItem
	{
		using namespace nsItemMessagePaperConstant;
		using namespace nsItemConstant;

		ItemMessagePaper::~ItemMessagePaper()
		{
			DeleteGO(m_paperModel);
		}

		bool ItemMessagePaper::Start()
		{
			m_paperModel = NewGO<SkinModelRender>(0);

			m_paperModel->Init("Assets/modelData/Paper.tkm");
			m_paperModel->SetPosition(m_position);

			return true;
		}

		void ItemMessagePaper::Update()
		{
			Vector3 dis = m_position - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、こちらの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Paper);
				m_player->GetPlayerTarget()->SetTargetMessagePaper(this);
			}

			//プレイヤーのターゲットがこのアイテムで、Aボタンが押されたら、入手
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Paper
				&& m_player->GetPlayerTarget()->GetTargetMessagePaper() == this)
			{
				//プレイヤーを読む状態にする。
				m_player->SetPlayerState(nsPlayer::Player::enState_Read);
				//読むテキストを送る。
				m_player->GetPlayerRead()->SetMessage(MESSAGEPAPAER_TEXT[m_kind]);
				//SE
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/ReadStart.wav");
				ss->Play(false);
			}
		}
	}
}