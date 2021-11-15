#include "stdafx.h"
#include "ItemFlashLightParts.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
namespace nsHikageri
{
	namespace nsItem
	{
		ItemFlashLightParts::~ItemFlashLightParts()
		{
			if (m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Key
				&& m_player->GetPlayerTarget()->GetTargetFlashLightParts() == this)
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_None);

			DeleteGO(m_partsModel);
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
			m_partsModel->Init("Assets/modelData/FlashLightParts.tkm");
			m_partsModel->SetPosition(m_position);

			return true;
		}

		void ItemFlashLightParts::Update()
		{
			Vector3 dis = m_position - m_player->GetPlayerMove()->GetPosition();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、こちらの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_FlashLightParts);
				m_player->GetPlayerTarget()->SetTargetFlashLightParts(this);
			}

			//プレイヤーのターゲットがこの鍵で、Aボタンが押されたら、入手
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_FlashLightParts
				&& m_player->GetPlayerTarget()->GetTargetFlashLightParts() == this)
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
					m_player->GetFlashLight()->GetAbilityMedousaEye()->SetAbilityActiveFlag(true);
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