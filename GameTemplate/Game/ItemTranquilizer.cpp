#include "stdafx.h"
#include "ItemInclude.h"
#include "ItemBase.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
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

			//エフェクトを停止
			m_shineEff.Stop();
		}
		bool ItemTranquilizer::Start()
		{
			m_tranquilizerModel = NewGO<SkinModelRender>(0);
			m_tranquilizerModel->SetMakeSkinModelRenderEX(true);
			m_tranquilizerModel->Init("Assets/modelData/Medicine.tkm");
			m_tranquilizerModel->SetPosition(m_position);

			//光るエフェクト
			m_shineEff.Init(u"Assets/effect/ItemEff.efk");
			m_shineEff.SetScale({ 50.0f,50.0,50.0f });
			m_shineEffPos = m_position;
			m_shineEffPos.y += SHINE_EFF_HEIGHT;
			m_shineEff.SetPosition(m_shineEffPos);
			m_shineEff.Play();

			return true;
		}

		void ItemTranquilizer::Update()
		{
			//光るエフェクト
			ExecuteShineEffect();

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

			//透視
			ExecuteClairvoyance();
		}

		//透視の処理
		void ItemTranquilizer::ExecuteClairvoyance()
		{
			if (m_player->GetFlashLight()->GetAbilityClairvoyance()->GetUseAbilityFlag())
			{
				m_tranquilizerModel->SetClairvoyanceCasterFlag(true);
			}
			else
			{
				m_tranquilizerModel->SetClairvoyanceCasterFlag(false);
			}
		}

		void ItemTranquilizer::Got()
		{
			SoundSource* ss = NewGO<SoundSource>(0);
			ss->Init(L"Assets/sound/GetItemTranquilizer.wav");
			ss->Play(false);
			m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_Tranquilizer);
			DeleteGO(this);
		}

		void ItemTranquilizer::ExecuteShineEffect()
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