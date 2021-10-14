#include "stdafx.h"
#include "PlayerAction.h"
#include "Player.h"
#include "PlayerMove.h"
#include "PlayerCamera.h"
#include "PlayerConstant.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerActionConstant;

		bool PlayerAction::Start()
		{
			return true;
		}

		void PlayerAction::ExecuteUpdate()
		{
			CrouchDown();
		}

		//屈むアクション
		void PlayerAction::CrouchDown()
		{
			if (m_crouchDownFlag == false)
			{
				//屈む。
				if (g_pad[0]->IsTrigger(enButtonLB3))
				{
					m_player->SetScale(CROUCHDOWN_PLAYER_SCALE);
					m_playerMove->SetCrouchDownFlag(true);
					m_playerCamera->SetPlEyeHeight(CROUCHDOWN_PLAYER_EYE_HEIGHT);
					m_crouchDownFlag = true;
				}
			}

			else if (m_crouchDownFlag == true)
			{
				if (g_pad[0]->IsTrigger(enButtonLB3))
				{
					m_player->SetScale(nsPlayerConstant::INI_PLAYER_SCALE);
					m_playerMove->SetCrouchDownFlag(false);
					m_playerCamera->SetPlEyeHeight(nsPlayerCameraConstant::INI_PLAYER_EYE_HEIGHT);
					m_crouchDownFlag = false;
				}
			}
		}
	}
}