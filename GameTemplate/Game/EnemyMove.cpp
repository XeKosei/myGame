#include "stdafx.h"
#include "EnemyMove.h"
#include "Enemy.h"
#include "EnemyConstant.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyMoveConstant;

		bool EnemyMove::Start()
		{
			return true;
		}

		//Player.cppのUpdate()で呼び出す処理
		void EnemyMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void EnemyMove::Move()
		{
			//エネミーの動く速さ
			m_moveSpeed = ENEMY_WALK_SPEED;	

			//スティックの傾きからプレイヤーの速度を計算
			Vector3 xSpeed = g_camera3D->GetRight() * g_pad[0]->GetLStickXF();
			Vector3 ySpeed = Cross(g_camera3D->GetRight(), Vector3::AxisY) * g_pad[0]->GetLStickYF();
			m_velocity += (xSpeed + ySpeed) * m_moveSpeed;

			//減速処理
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			//プレイヤーを上に動かす(仮)
			if (g_pad[0]->IsTrigger(enButtonRB2))
				m_velocity.y += 30.0f;

			//重力
			if (m_enemy->GetCharaCon()->IsOnGround() == false)
			{	//地面についていなかったら
				m_velocity.y -= pow(GRAVITY_SPEED, GRAVITY_INDEX);	//重力を与える
			}

			//速度がほぼ0ならば、0にする。
			if (fabsf(m_velocity.x + m_velocity.z) < 0.001f)
			{
				m_velocity.x = 0.0f;
				m_velocity.z = 0.0f;
			}

			//位置に速度を加算
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);
			//m_position += m_velocity;
			//位置を設定する。
			m_enemy->SetPosition(m_position);
		}

		void EnemyMove::Turn()
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
				m_enemy->SetRotation(m_qRot);
			}
		}

	}
}