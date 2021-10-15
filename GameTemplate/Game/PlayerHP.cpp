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

		/// @brief プレイヤーのダメージを指定した値だけ減らす。
		/// @param damageNum 与えるダメージ
		void PlayerHP::Damage(int damageNum)
		{
			m_HP -= damageNum;

			//体力が0になったら
			if (m_HP <= 0)
			{
				m_HP = 0;
				m_player->SetDeadFlag(true);
			}
		}




	}
}