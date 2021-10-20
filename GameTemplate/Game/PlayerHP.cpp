#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerHPConstant;

		bool PlayerHP::Start()
		{
			//�ő�HP��ݒ�
			m_HP = MAX_PLAYER_HP;
			return true;
		}

		void PlayerHP::ExecuteUpdate()
		{
			//�C���^�[�o�����J�E���g
			if (m_damageIntervalCount != 0)
			{
				m_damageIntervalCount--;
			}
		}

		/// @brief �v���C���[�̃_���[�W���w�肵���l�������炷�B
		/// @param damageNum �^����_���[�W
		void PlayerHP::Damage(int damageNum)
		{
			//�C���^�[�o���łȂ����
			//if (m_damageIntervalCount == 0)
			//{
				m_HP -= damageNum;

				//�̗͂�0�ɂȂ�����
				if (m_HP <= 0)
				{
					m_HP = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}
				//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̃C���^�[�o����ݒ�B
				m_damageIntervalCount = DAMAGE_INTERVAL;
			//}
		}
	}
}