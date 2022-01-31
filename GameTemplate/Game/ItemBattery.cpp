#include "stdafx.h"
#include "ItemInclude.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"

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

			//�G�t�F�N�g���~
			m_shineEff.Stop();
		}
		bool ItemBattery::Start()
		{
			m_batteryModel = NewGO<SkinModelRender>(0);
			m_batteryModel->SetMakeSkinModelRenderEX(true);
			m_batteryModel->Init("Assets/modelData/Battery.tkm");
			m_batteryModel->SetPosition(m_position);

			//����G�t�F�N�g
			m_shineEff.Init(u"Assets/effect/ItemEff.efk");
			m_shineEff.SetScale({ 50.0f,50.0,50.0f });
			m_shineEffPos = m_position;
			m_shineEffPos.y += SHINE_EFF_HEIGHT;
			m_shineEff.SetPosition(m_shineEffPos);
			m_shineEff.Play();

			return true;
		}

		void ItemBattery::Update()
		{
			//�G�t�F�N�g�Đ�
			ExecuteShineEffect();

			Vector3 dis = m_position - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//�v���C���[�Ƃ̋������߂��A������̕��������Ă�����
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Battery);
				m_player->GetPlayerTarget()->SetTargetBattery(this);
			}

			//����
			ExecuteClairvoyance();
		}

		//�����̏���
		void ItemBattery::ExecuteClairvoyance()
		{
			if (m_player->GetFlashLight()->GetAbilityClairvoyance()->GetUseAbilityFlag())
			{
				m_batteryModel->SetClairvoyanceCasterFlag(true);
			}
			else
			{
				m_batteryModel->SetClairvoyanceCasterFlag(false);
			}
		}

		//���肳�ꂽ�Ƃ�
		void ItemBattery::Got()
		{
			//�v���C���[�̃^�[�Q�b�g�����̃A�C�e���ŁAA�{�^���������ꂽ��A����
			SoundSource* ss = NewGO<SoundSource>(0);
			ss->Init(L"Assets/sound/GetItemBattery.wav");
			ss->Play(false);
			m_player->GetPlayerPouch()->AddItem(nsPlayer::PlayerPouch::enItem_Battery);
			DeleteGO(this);		
		}

		void ItemBattery::ExecuteShineEffect()
		{
			//����G�t�F�N�g
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