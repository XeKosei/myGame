#include "stdafx.h"
#include "ItemKey.h"
#include "ItemBase.h"
#include "ItemInclude.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
namespace nsHikageri
{
	using namespace nsGimmick;
	namespace nsItem
	{
		using namespace nsItemConstant;

		ItemKey::~ItemKey()
		{
			DeleteGO(m_keyModel);
			//エフェクトを停止
			m_shineEff.Stop();
		}
		bool ItemKey::Start()
		{
			m_keyModel = NewGO<SkinModelRender>(0);
			m_keyModel->SetMakeSkinModelRenderEX(true);
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

			//光るエフェクト
			m_shineEff.Init(u"Assets/effect/ItemEff.efk");
			m_shineEff.SetScale({ 50.0f,50.0,50.0f });
			m_shineEffPos = m_position;
			m_shineEffPos.y += SHINE_EFF_HEIGHT;
			m_shineEff.SetPosition(m_shineEffPos);
			m_shineEff.Play();

			return true;
		}

		void ItemKey::Update()
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
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Key);
				m_player->GetPlayerTarget()->SetTargetKey(this);
			}

			//透視
			ExecuteClairvoyance();
		}

		//透視の処理
		void ItemKey::ExecuteClairvoyance()
		{
			if (m_player->GetFlashLight()->GetAbilityClairvoyance()->GetUseAbilityFlag())
			{
				m_keyModel->SetClairvoyanceCasterFlag(true);
			}
			else
			{
				m_keyModel->SetClairvoyanceCasterFlag(false);
			}
		}

		void ItemKey::Got()
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

			m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_None);

			//SE
			SoundSource* ss = NewGO<SoundSource>(0);
			ss->Init(L"Assets/sound/GetItemKey.wav");
			ss->Play(false);
			
		}

		void ItemKey::ExecuteShineEffect()
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