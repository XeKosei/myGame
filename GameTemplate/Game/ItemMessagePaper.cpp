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

			//�G�t�F�N�g���~
			m_shineEff.Stop();
		}

		bool ItemMessagePaper::Start()
		{
			m_paperModel = NewGO<SkinModelRender>(0);

			m_paperModel->Init("Assets/modelData/Paper.tkm");
			m_paperModel->SetPosition(m_position);

			//����G�t�F�N�g
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
			//����G�t�F�N�g
			m_shineEff.Update();

			Vector3 dis = m_position - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//�v���C���[�Ƃ̋������߂��A������̕��������Ă�����
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Paper);
				m_player->GetPlayerTarget()->SetTargetMessagePaper(this);
			}

			//�v���C���[�̃^�[�Q�b�g�����̃A�C�e���ŁAA�{�^���������ꂽ��A����
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Paper
				&& m_player->GetPlayerTarget()->GetTargetMessagePaper() == this)
			{
				//�v���C���[��ǂޏ�Ԃɂ���B
				m_player->SetPlayerState(nsPlayer::Player::enState_Read);
				//�ǂރe�L�X�g�𑗂�B
				m_player->GetPlayerRead()->SetMessage(MESSAGEPAPAER_TEXT[m_kind]);
				//SE
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/ReadStart.wav");
				ss->Play(false);
			}
		}
	}
}