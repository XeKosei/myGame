#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerHPConstant;

		bool PlayerHP::Start()
		{
			//最大HPを設定
			m_HP = MAX_PLAYER_HP;
			return true;
		}

		void PlayerHP::ExecuteUpdate()
		{
			//インターバルをカウント
			if (m_damageIntervalCount != 0)
			{
				m_damageIntervalCount--;
			}
		}

		/// @brief プレイヤーのダメージを指定した値だけ減らす。
		/// @param damageNum 与えるダメージ
		void PlayerHP::Damage(int damageNum)
		{
			//インターバルでなければ
			//if (m_damageIntervalCount == 0)
			//{
				m_HP -= damageNum;

				//体力が0になったら
				if (m_HP <= 0)
				{
					m_HP = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}
				//次にダメージを受けられるようになるまでのインターバルを設定。
				m_damageIntervalCount = DAMAGE_INTERVAL;
			//}
		}
	}
}