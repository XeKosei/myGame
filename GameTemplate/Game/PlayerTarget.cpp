#include "stdafx.h"
#include "PlayerInclude.h"
#include "Door.h"
#include "ItemInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerTargetConstant;
		PlayerTarget::~PlayerTarget()
		{
			
		}

		void PlayerTarget::Init(Player* pl)
		{
			m_player = pl;

			m_itemNameFont = NewGO<FontRender>(3);
			m_itemNameFont->SetPosition(ITEMNAME_FONT_POS);
			m_itemNameFont->SetScale(ITEMNAME_FONT_SCALE);
			m_itemNameFont->SetShadowFlag(true);
			m_itemNameFont->SetShadowColor(Vector4::Black);
			m_itemNameFont->SetShadowOffset(ITEMNAME_FONT_SCALE);
			/*m_commandFont = NewGO<FontRender>(0);
			m_commandFont->SetPosition(COMMAND_FONT_POS);
			m_commandFont->SetShadowFlag(true);
			m_commandFont->SetShadowColor(Vector4::Black);*/
			//m_commandFont->SetShadowOffset();

		}

		void PlayerTarget::ExecuteUpdate()
		{
			m_itemNameFont->SetText(TARGET_NAME[m_target]);

			Vector3 targetPos = Vector3::Zero;

			switch (m_target)
			{
			case enTarget_None:
				//m_commandFont->SetText(COMMAND_TEXT[enCommand_None]);
				return;
				break;
			case enTarget_Door:
				/*if (m_targetDoor->GetOpenFlag())
					m_commandFont->SetText(COMMAND_TEXT[enCommand_Close]);
				else
					m_commandFont->SetText(COMMAND_TEXT[enCommand_Open]);*/
				targetPos = m_targetDoor->GetPosition();
				break;
			case enTarget_Key:
				//m_commandFont->SetText(COMMAND_TEXT[enCommand_Get]);
				targetPos = m_targetKey->GetPosition();
				break;
			case enTarget_FlashLightParts:
				//m_commandFont->SetText(COMMAND_TEXT[enCommand_Get]);
				targetPos = m_targetFlashLightParts->GetPosition();
				break;
			case enTarget_Tranquilizer:
				//m_commandFont->SetText(COMMAND_TEXT[enCommand_Get]);
				targetPos = m_targetTranquilizer->GetPosition();
				break;
			case enTarget_Battery:
				//m_commandFont->SetText(COMMAND_TEXT[enCommand_Get]);
				targetPos = m_targetBattery->GetPosition();
				break;
			case enTarget_Paper:
				//m_commandFont->SetText(COMMAND_TEXT[enCommand_Read]);
				targetPos = m_targetMessagePaper->GetPosition();
				break;
			default:
				break;
			}

			Vector3 toTargetDis = targetPos - m_player->GetPlayerCamera()->GetCameraPos();
			Vector3 toTargetDir = toTargetDis;
			toTargetDir.Normalize();
			//ターゲットとの距離が離れたり、目線が外れたら、ターゲットを解除
			if ((toTargetDis).Length() > CATCH_EYES_DIS
				|| Dot(toTargetDir, m_player->GetPlayerCamera()->GetDirection()) < CATCH_EYES_DOT)
			{
				m_target = enTarget_None;
			}
		}
	}
}
