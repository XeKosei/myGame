#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemySearchPlayerConstant;

		bool EnemySearchPlayer::Start()
		{
			m_position = m_searchPos[0];
			return true;
		}

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//移動処理(仮)
			Move();
			Turn();

			//エネミーの位置からプレイヤーの位置へのベクトルを求める
			Vector3 toTargetDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_position;
			toTargetDir.Normalize();

			//エネミーの向きとの内積が一定以上なら、プレイヤーを追いかけ始める。
			if (Dot(toTargetDir, m_dir) >= 0.9f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
			}
		}

		void EnemySearchPlayer::Move()
		{
			if (m_searchFlag == false)
			{
				m_targetPos = m_searchPos[1];		
			}
			else
			{
				m_targetPos = m_searchPos[0];
			}

			m_dir = m_targetPos - m_position;
			m_dir.Normalize();

			m_velocity = m_dir * ENEMY_WALK_SPEED;
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);
			m_enemy->GetEnemyModel()->SetPosition(m_position);

			if ((m_targetPos - m_position).Length() <= 5.0f)
			{
				m_searchFlag = !m_searchFlag;
			}

		}
		void EnemySearchPlayer::Turn()
		{
			if (m_velocity.x != 0.0f || m_velocity.z != 0.0f)
			{
				//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
				//cameraDir.x / cameraDir.zの結果はtanθになる。
				//atan2を使用して、角度を求めている。
				//これが回転角度になる。
				float angle = atan2(m_velocity.x, m_velocity.z);
				//atanが返してくる角度はラジアン単位なので
				//SetRotationDegではなくSetRotationを使用する。
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_enemy->GetEnemyModel()->SetRotation(m_qRot);
			}
		}
	}
}