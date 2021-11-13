#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyChaseConstant;

		bool EnemyChase::Start()
		{
			return true;
		}

		//Enemy.cppのUpdate()で呼び出す処理
		void EnemyChase::ExecuteUpdate()
		{
			Chase();

			//距離が一定以内まで縮まったら、攻撃に移行。
			if ((m_enemy->GetEnemyMove()->GetTarget() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= ENEMY_CAN_ATTACK_DIS
				&& m_enemy->GetPlayer()->GetPlayerState() == nsPlayer::Player::enState_Normal)
			{
				//エネミーを噛みつき状態にする
				m_enemy->SetEnemyState(Enemy::enState_Attack);
				//プレイヤーを噛みつかれ状態にする
				m_enemy->GetPlayer()->SetPlayerState(nsPlayer::Player::enState_Bitten);
				//プレイヤーが噛みつかれている相手を、このエネミーに設定y
				m_enemy->GetPlayer()->GetPlayerBitten()->SetEnemy(m_enemy);
			}
		}

		void EnemyChase::Chase()
		{
			//ターゲットをプレイヤーの位置に指定
			m_enemy->GetEnemyMove()->SetTarget(m_enemy->GetPlayer()->GetPlayerMove()->GetPosition());
			//移動速度を指定
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_DASH_SPEED);

			
		}				
	}
}