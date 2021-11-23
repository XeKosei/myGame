#include "stdafx.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerActionConstant;

		PlayerAction::~PlayerAction()
		{

		}

		bool PlayerAction::Start()
		{
			return true;
		}

		void PlayerAction::ExecuteUpdate()
		{
			CrouchDown();
		}

		//���ރA�N�V����
		void PlayerAction::CrouchDown()
		{
			if (m_crouchDownFlag == false)
			{
				//���ށB
				if (g_pad[0]->IsTrigger(enButtonLB3))
				{
					m_player->GetPlayerModel()->SetScale(CROUCHDOWN_PLAYER_SCALE);
					m_player->GetPlayerCamera()->SetPlEyeHeight(CROUCHDOWN_PLAYER_EYE_HEIGHT);
					m_crouchDownFlag = true;
				}
			}

			else if (m_crouchDownFlag == true)
			{
				if (g_pad[0]->IsTrigger(enButtonLB3))
				{
					m_player->GetPlayerModel()->SetScale(nsPlayerConstant::INI_PLAYER_SCALE);
					m_player->GetPlayerCamera()->SetPlEyeHeight(nsPlayerCameraConstant::INI_PLAYER_EYE_HEIGHT);
					m_crouchDownFlag = false;
				}
			}
		}
	}
}