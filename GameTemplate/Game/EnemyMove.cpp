#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "TknFile.h"
#include "BackGround.h"
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

		//経路探索で、道を調べる処理
		void EnemyMove::RouteSearch(Vector3 pos, Vector3 targetPos)
		{
			m_targetPos = targetPos;
			// パス検索
			m_pathFiding.Execute(
				m_path,							// 構築されたパスの格納先
				m_nvmMesh,						// ナビメッシュ
				pos,						// 開始座標
				targetPos,					// 移動目標座標
				PhysicsWorld::GetInstance(),	// 物理エンジン	
				10.0f,							// AIエージェントの半径
				120.0f							// AIエージェントの高さ。
			);
		}

		//経路探索での移動処理
		void EnemyMove::RouteSearchMove()
		{
			/*if (g_pad[0]->IsTrigger(enButtonA))
			{
				QueryGOs<nsBackGround::BackGround>("backGround", [this](nsBackGround::BackGround* backGround)->bool {
					Vector3 pos = Vector3::Zero;
					Vector3 startPos = m_position;
					startPos.y += 10.0f;
					Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
					endPos.y += 10.0f;

					if (backGround->GetStageModel()->isLineHitModel(startPos, endPos, pos) == false)
					{
						m_enemy->SetEnemyState(Enemy::enState_Scream);
					}
					return true;
					}
				);
			}*/

			Vector3 oldPos = m_position;

			bool isEnd;		
			
			//パス上を移動する。
			m_position = m_path.Move(
				m_position,
				5.0f,
				isEnd
			);

			//向きと速度
			m_velocity = m_position - oldPos;
			m_direction = m_velocity;
			m_direction.Normalize();

			//位置を設定
			m_enemy->GetEnemyMove()->SetPosition(m_position);
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