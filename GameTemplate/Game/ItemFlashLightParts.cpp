#include "stdafx.h"
#include "ItemInclude.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
namespace nsHikageri
{
	namespace nsItem
	{
		using namespace nsItemConstant;

		ItemFlashLightParts::~ItemFlashLightParts()
		{
			if (m_player != nullptr)
			{
				if (m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_FlashLightParts
					&& m_player->GetPlayerTarget()->GetTargetFlashLightParts() == this)
				{
					m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_None);
				}
			}

			DeleteGO(m_partsModel);

			//エフェクトを停止
			m_shineEff.Stop();
		}

		bool ItemFlashLightParts::Start()
		{
			m_partsModel = NewGO<SkinModelRender>(0);
			/*switch (m_partsType)
			{
			case enFlashLightPartsTypes_StrobeFlash:
				m_partsModel->Init("Assets/modelData/Key.tkm");
				break;
			case enFlashLightPartsTypes_Clairvoyance:
				m_partsModel->Init("Assets/modelData/Key.tkm");
				break;
			case enFlashLightPartsTypes_MedousaEye:
				m_partsModel->Init("Assets/modelData/Key.tkm");
				break;
			default:
				m_partsModel->Init("Assets/modelData/Door.tkm");
				break;
			};*/
			m_partsModel->SetMakeSkinModelRenderEX(true);
			m_partsModel->Init("Assets/modelData/FlashLightParts.tkm");
			m_partsModel->SetPosition(m_position);

			//光るエフェクト
			m_shineEff.Init(u"Assets/effect/ItemEff.efk");
			m_shineEff.SetScale({ 50.0f,50.0,50.0f });
			m_shineEffPos = m_position;
			m_shineEffPos.y += SHINE_EFF_HEIGHT;
			m_shineEff.SetPosition(m_shineEffPos);
			m_shineEff.Play();

			return true;
		}

		void ItemFlashLightParts::Update()
		{
			//光るエフェクト
			m_shineEff.Update();

			Vector3 dis = m_position - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、こちらの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_FlashLightParts);
				m_player->GetPlayerTarget()->SetTargetFlashLightParts(this);
			}

			ExecuteClairvoyance();
		}

		//透視の処理
		void ItemFlashLightParts::ExecuteClairvoyance()
		{
			if (m_player->GetFlashLight()->GetAbilityClairvoyance()->GetUseAbilityFlag())
			{
				m_partsModel->SetClairvoyanceCasterFlag(true);
			}
			else
			{
				m_partsModel->SetClairvoyanceCasterFlag(false);
			}
		}

		void ItemFlashLightParts::Got()
		{
			switch (m_partsType)
			{
			case enFlashLightPartsTypes_StrobeFlash:
				m_player->GetFlashLight()->GetAbilityStrobeFlash()->SetAbilityActiveFlag(true);
				break;
			case enFlashLightPartsTypes_Clairvoyance:
				m_player->GetFlashLight()->GetAbilityClairvoyance()->SetAbilityActiveFlag(true);
				break;
			case enFlashLightPartsTypes_MedousaEye:
				m_player->GetFlashLight()->GetAbilityStrobeFlash()->SetAbilityActiveFlag(true);
				m_player->GetFlashLight()->GetAbilityMedousaEye()->SetAbilityActiveFlag(true);
				break;
			default:
				return;
				break;
			}
			DeleteGO(this);

			//SE
			SoundSource* ss = NewGO<SoundSource>(0);
			ss->Init(L"Assets/sound/GetFlashLightParts.wav");
			ss->Play(false);

		}
	}
}