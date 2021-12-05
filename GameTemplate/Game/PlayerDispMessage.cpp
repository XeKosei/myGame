#include "stdafx.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		bool PlayerDispMessage::Start()
		{
			m_messageFont = NewGO<FontRender>(0);
			m_messageFont->SetText(L"");
			m_messageFont->SetScale(0.7f);
			m_messageFont->SetShadowFlag(true);
			m_messageFont->SetShadowColor(m_messageFontColor);
			m_messageFont->SetShadowOffset(0.7f);

			return true;
		}

		void PlayerDispMessage::ExecuteUpdate()
		{
			if (m_setMessageFlag)
			{
				//m_messageFontColor.r
			}
		}

		void PlayerDispMessage::SetMessage(std::wstring message)
		{

		}
	}
}