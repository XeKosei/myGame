#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyAttackConstant;
		bool EnemyAttack::Start()
		{
			//攻撃モーションの時間を設定。
			m_attackMotionCount = ATTACKMOTION_TIME;

			//エネミーに噛みつかれ続ける時間
			m_enemyBiteCount = BITING_TIME;

			return true;
		}
		void EnemyAttack::ExecuteUpdate()
		{
			//Attack();
			switch (m_biteState)
			{
			case enBiteState_PreBite:
				PreBite();
				break;
			case enBiteState_Bite:
				Bite();
				break;
			case enBiteState_EndBite:
				EndBite();
				break;
			default:
				break;
			}
		}

		void EnemyAttack::Attack()
		{
			//攻撃行動の時間をカウント
			m_attackMotionCount--;

			//攻撃判定のある時間ならば
			if (m_attackMotionCount >= ATTACKMOTION_HIT_START_TIME
				&& m_attackMotionCount <= ATTACKMOTION_HIT_END_TIME)
			{
				//プレイヤーへのベクトル
				Vector3 toPlayerDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
				//エネミーの向き
				Vector3 enemyDir = m_enemy->GetEnemyMove()->GetDirection();

				if (Dot(toPlayerDir, enemyDir) >= ATTACKMOTION_HIT_DOT && toPlayerDir.Length() <= ATTACKMOTION_HIT_DIS)
				{
					m_enemy->GetPlayer()->GetPlayerSanity()->Damage(0);
				}
			}
			//カウントが終わったら、エネミーの状態を追跡モードに移行し、リセット
			else if (m_attackMotionCount <= -50)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
				m_attackMotionCount = ATTACKMOTION_TIME;
			}		
		}

		//噛みつきの最初の処理
		void EnemyAttack::PreBite()
		{
			//エネミーの向きを設定
			Vector3 dir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_enemy->GetEnemyModel()->SetRotation(qRot);

			//アニメーションが終わったら次のステップへ
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_biteState = enBiteState_Bite;
			}
		}

		//噛みつき中の処理
		void EnemyAttack::Bite()
		{
			//噛みつかれる時間をカウント
			m_enemyBiteCount--;
			//アニメーションの時間をカウント
			m_enemyBiteAnimCount++;

			//アニメーションが噛みつきモーション中なら、ダメージを与える。
			if (m_enemyBiteAnimCount == BITEANIM_BITE_TIMING)
			{
				m_enemy->GetPlayer()->GetPlayerSanity()->Damage(BITE_DAMAGE);
			}
			//アニメーションが1ループしたら
			else if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				//アニメーションをカウントリセット
				m_enemyBiteAnimCount = 0;
				//アニメーションをリセットするために、一度別のアニメーションを挟む(上書きされるのでこれは再生されない。)
				m_enemy->GetEnemyModel()->PlayAnimation(EnemyAnim::enAnimationClip_Idle);
			}

			//カウントが終わったら、次のステップへ移行
			if (m_enemyBiteCount <= 0)
			{
				m_biteState = enBiteState_EndBite;
			}
		}

		//噛みつきの終わった後の処理
		void EnemyAttack::EndBite()
		{
			//アニメーションが終わったら、
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				//エネミーを追跡状態に移行して、リセット
				m_biteState = enBiteState_PreBite;
				m_enemy->SetEnemyState(Enemy::enState_Scream);
				m_enemyBiteCount = BITING_TIME;
				m_enemyBiteAnimCount = 0;
			}
		}
	}
}