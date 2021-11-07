#include "stdafx.h"
#include "PlayerInclude.h"
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		void PlayerTarget::ExecuteUpdate()
		{
			Vector3 targetPos = Vector3::Zero;

			//�^�[�Q�b�g�̈ʒu���擾
			switch (m_target)
			{
			case enTarget_None:
				return;
				break;
			case enTarget_Door:
				targetPos = m_targetDoor->GetPosition();
				break;
			default:
				break;
			}

			//�^�[�Q�b�g�Ƃ̋��������ꂽ��A�^�[�Q�b�g������
			if ((targetPos - m_player->GetPlayerMove()->GetPosition()).Length() > 500.0f)
			{
				m_target = enTarget_None;
			}
		}
	}
}
