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

			//エフェクトを停止
			m_shineEff.Stop();
		}

		bool ItemMessagePaper::Start()
		{
			m_paperModel = NewGO<SkinModelRender>(0);

			m_paperModel->Init("Assets/modelData/Paper.tkm");
			m_paperModel->SetPosition(m_position);

			//光るエフェクト
			m_shineEff.Init(u"Assets/effect/ItemEff.efk");
			m_shineEff.SetScale({ 50.0f,50.0,50.0f });
			m_shineEffPos = m_position;
			m_shineEffPos.y += SHINE_EFF_HEIGHT;
			m_shineEff.SetPosition(m_shineEffPos);
			m_shineEff.Play();

			return true;
		}

		void ItemMessagePaper::Update()
		{
			//エフェクト再生
			ExecuteShineEffect();

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
		}

		void ItemMessagePaper::Read()
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

		void ItemMessagePaper::ExecuteShineEffect()
		{
			//光るエフェクト
			if (m_shineEffPlayingFlag)
			{
				m_shineEff.Update();
				if (m_player->GetPlayerState() == nsPlayer::Player::enState_Read)
				{
					m_shineEff.Stop();
					m_shineEffPlayingFlag = false;
				}
			}
			else
			{
				if (m_player->GetPlayerState() != nsPlayer::Player::enState_Read)
				{
					m_shineEff.Play();
					m_shineEffPlayingFlag = true;
				}
			}
		}
	}
}