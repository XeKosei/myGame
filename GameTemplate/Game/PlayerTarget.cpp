#include "stdafx.h"
#include "PlayerInclude.h"
#include "Door.h"
#include "ItemInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		PlayerTarget::~PlayerTarget()
		{
			
		}

		void PlayerTarget::ExecuteUpdate()
		{
			Vector3 targetPos = Vector3::Zero;

			//ターゲットの位置を取得
			switch (m_target)
			{
			case enTarget_None:
				return;
				break;
			case enTarget_Door:
				targetPos = m_targetDoor->GetPosition();
				break;
			case enTarget_Key:
				targetPos = m_targetKey->GetPosition();
				break;
			case enTarget_FlashLightParts:
				targetPos = m_targetFlashLightParts->GetPosition();
				break;
			case enTarget_Tranquilizer:
				targetPos = m_targetTranquilizer->GetPosition();
				break;
			case enTarget_Battery:
				targetPos = m_targetBattery->GetPosition();
				break;
			default:
				break;
			}

			//ターゲットとの距離が離れたら、ターゲットを解除
			if ((targetPos - m_player->GetPlayerMove()->GetPosition()).Length() > 500.0f)
			{
				m_target = enTarget_None;
			}
		}
	}
}
