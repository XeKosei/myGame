#include "stdafx.h"
#include "GimmickInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsGimmick
	{
		using namespace nsChandelierManagerConstant;

		ChandelierManager::~ChandelierManager()
		{
			for (int chandelierNum = 0; chandelierNum < CHANDELIER_NUM; chandelierNum++)
			{
				DeleteGO(m_chandelier[chandelierNum]);
			}
			for (int i = 0; i < 2; i++)
			{
				DeleteGO(m_spotLig[i]);
			}
		}

		bool ChandelierManager::Start()
		{
			////�V�����f���A�@�e�X�g
			for (int chandelierNum = 0; chandelierNum < CHANDELIER_NUM; chandelierNum++)
			{
				m_chandelier[chandelierNum] = NewGO<nsGimmick::Chandelier>(1);
				m_chandelier[chandelierNum]->SetPlayer(m_player);
				m_chandelier[chandelierNum]->SetEnemy(m_enemy);
				m_chandelier[chandelierNum]->SetPosition(m_chandelierPos[chandelierNum]);
			}

			for (int i = 0; i < 2; i++)
			{
				//�X�|�b�g���C�g
				m_spotLig[i] = NewGO<SpotLight>(0);
				m_spotLig[i]->SetColor(CHANDELIER_SPOTLIGHT_COLOR);
				m_spotLig[i]->SetPosition(m_chandelierPos[i]);
				m_spotLig[i]->SetRange(CHANDELIER_SPOTLIGHT_RANGE);
				m_spotLig[i]->SetAngle(CHANDELIER_SPOTLIGHT_ANGLE / 2);	//���a�Ȃ̂�2�Ŋ���
				Vector3 targetPos = m_chandelierPos[i];
				targetPos.y = 0.0f;
				Vector3 dir = targetPos - m_chandelierPos[i];
				dir.Normalize();
				m_spotLig[i]->SetDirection(dir);

				//�X�|�b�g���C�g�̔ԍ�1�͉����d���̃X�|�b�g���C�g�Ȃ̂ŁAi��+1����B
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_chandelierPos[i], i + 1);				
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(targetPos, i + 1);
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(CHANDELIER_SPOTLIGHT_ANGLE, i + 1);
				nsHikageri::LightManager::GetInstance()->SetIsFlashLightSwitchOn(1, i+1);
			}

			return true;
		}
		void ChandelierManager::Update()
		{
			//�v���C���[�Ƃ̋������߂���ɃX�|�b�g���C�g�ƃ��C�g�J�������t������B
			Vector3 plPos = m_player->GetPlayerMove()->GetPosition();
			float toPlDis = (plPos - m_chandelierPos[0]).Length();
			int cameraPosNo[2] = { 0,1 };
			for (int no = 1; no < CHANDELIER_NUM; no++)
			{
				float dis = (plPos - m_chandelierPos[no]).Length();
				if (dis < toPlDis)
				{
					cameraPosNo[1] = cameraPosNo[0];
					cameraPosNo[0] = no;
					toPlDis = dis;
				}
			}

			for (int i = 0; i < 2; i++)
			{
				m_spotLig[i]->SetPosition(m_chandelierPos[cameraPosNo[i]]);
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_chandelierPos[cameraPosNo[i]], i + 1);
				Vector3 targetPos = m_chandelierPos[cameraPosNo[i]];
				targetPos.y = 0.0f;
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(targetPos, i + 1);
			}
		}
	}
}
