#include "stdafx.h"
#include "PlayerHP.h"
#include "Player.h"
#include "PlayerConstant.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerHPConstant;

		bool PlayerHP::Start()
		{
			m_HP = MAX_PLAYER_HP;
			return true;
		}

		/// @brief �v���C���[�̃_���[�W���w�肵���l�������炷�B
		/// @param damageNum �^����_���[�W
		void PlayerHP::Damage(int damageNum)
		{
			m_HP -= damageNum;

			//�̗͂�0�ɂȂ�����
			if (m_HP <= 0)
			{
				m_HP = 0;
				m_player->SetDeadFlag(true);
			}
		}




	}
}