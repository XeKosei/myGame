#include "stdafx.h"
#include "GimmickInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsGimmick
	{
		bool ChandelierManager::Start()
		{
			////シャンデリア　テスト
			for (int chandelierNum = 0; chandelierNum < 10; chandelierNum++)
			{
				m_chandelier[chandelierNum] = NewGO<nsGimmick::Chandelier>(1);
				m_chandelier[chandelierNum]->SetPlayer(m_player);
				m_chandelier[chandelierNum]->SetEnemy(m_enemy);
				m_chandelier[chandelierNum]->SetPosition(m_chandelierPos[chandelierNum]);
			}

			for (int i = 0; i < 2; i++)
			{
				//スポットライト
				m_spotLig[i] = NewGO<SpotLight>(0);
				m_spotLig[i]->SetColor({ 10.0f,10.0f,10.0f });
				m_spotLig[i]->SetPosition(m_chandelierPos[i]);
				m_spotLig[i]->SetRange(10000);
				m_spotLig[i]->SetAngle(1);
				Vector3 targetPos = m_chandelierPos[i];
				targetPos.y = 0.0f;
				Vector3 dir = targetPos - m_chandelierPos[i];
				dir.Normalize();
				m_spotLig[i]->SetDirection(dir);

				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_chandelierPos[i], i + 1);				
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(targetPos, i + 1);
				nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(2, i + 1);
			}

			return true;
		}
		void ChandelierManager::Update()
		{
			Vector3 plPos = m_player->GetPlayerMove()->GetPosition();
			float toPlDis = (plPos - m_chandelierPos[0]).Length();
			int cameraPosNo[2] = { 0,1 };
			for (int no = 1; no < 10; no++)
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
