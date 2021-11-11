#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "TknFile.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyMoveConstant;

		bool EnemyMove::Start()
		{
			// ナビメッシュを構築。
			m_nvmMesh.Init("Assets/nvm/nvmTest.tkn");
			return true;
		}

		void EnemyMove::ExecuteUpdate()
		{
			//Move();
			Turn();

			RouteSearchMove();
		}

		void EnemyMove::Move()
		{
			//ターゲットとエネミーとのベクトルを計算。
			m_direction = m_targetPos - m_position;
			m_direction.Normalize();

			//移動処理
			if (m_slowMoveFlag == false)
				m_velocity = m_direction * m_moveSpeed;
			else
				m_velocity = m_direction * ENEMY_SLOWWALK_SPEED;

			m_velocity *= GameTime::GetInstance().GetFrameDeltaTime();

			//減速処理
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

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

			//ターゲット地点にほぼ到達したら、
			if ((m_position - m_targetPos).Length() < 5.0f)
			{
				m_position = m_targetPos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
			}
			
			//モデル位置を設定する。
			m_enemy->GetEnemyModel()->SetPosition(m_position);	
		}
		void EnemyMove::RouteSearchMove()
		{
			bool isEnd;
			if (g_pad[0]->IsTrigger(enButtonA)) {
				// パス検索
				m_pathFiding.Execute(
					m_path,							// 構築されたパスの格納先
					m_nvmMesh,						// ナビメッシュ
					m_position,						// 開始座標
					m_enemy->GetPlayer()->GetPlayerMove()->GetPosition(),			// 移動目標座標
					PhysicsWorld::GetInstance(),	// 物理エンジン	
					50.0f,							// AIエージェントの半径
					200.0f							// AIエージェントの高さ。
				);
			}
			 //パス上を移動する。
			m_position = m_path.Move(
				m_position,
				5.0f,
				isEnd
			);
			m_enemy->GetEnemyModel()->SetPosition(m_position);

		}

		void EnemyMove::Turn()
		{
			if (m_velocity.x != 0.0f || m_velocity.z != 0.0f)
			{
				//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
				//m_direction.x / m_direction.zの結果はtanθになる。
				//atan2を使用して、角度を求めている。
				//これが回転角度になる。
				float angle = atan2(m_direction.x, m_direction.z);
				//atanが返してくる角度はラジアン単位なので
				//SetRotationDegではなくSetRotationを使用する。
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_enemy->GetEnemyModel()->SetRotation(m_qRot);
			}
		}
	}
}