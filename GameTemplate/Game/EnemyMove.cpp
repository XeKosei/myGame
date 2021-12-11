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

		EnemyMove::~EnemyMove()
		{

		}

		void EnemyMove::Init(Enemy* enemy)
		{
			m_enemy = enemy;
			// ナビメッシュを構築。
			m_nvmMesh.Init("Assets/nvm/nvmTest.tkn");
		}

		void EnemyMove::ExecuteUpdate()
		{
			switch (m_moveState)
			{
			case enMoveState_Straight:
				Move();
				break;
			case enMoveState_RouteSearch:
				RouteSearchMove();
				break;
			};		

			Turn();
			FootStepsSE();
		}

		void EnemyMove::SetPosition(Vector3 pos) {
			m_position = pos;
			m_enemy->GetEnemyModel()->SetPosition(m_position);
			m_enemy->GetCharaCon()->SetPosition(m_position);
		}

		void EnemyMove::Move()
		{
		
			//ターゲットとエネミーとのベクトルを計算。
			m_direction = m_targetPos - m_position;
			m_direction.Normalize();

			//移動処理
			if (m_slowMoveFlag)
			{
				m_moveSpeed = ENEMY_SLOWWALK_SPEED;
			}

			m_velocity += m_direction * m_moveSpeed * GameTime::GetInstance().GetFrameDeltaTime();

			//減速処理
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			m_direction = m_velocity;
			m_direction.Normalize();

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
			SetPosition(m_position);	
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
			Vector3 oldPos = m_position;

			bool isEnd;		
			
			//移動処理
			if (m_slowMoveFlag)
			{
				m_moveSpeed = ENEMY_SLOWWALK_SPEED;
			}

			//パス上を移動する。
			Vector3 pathPos = m_path.Move(
				m_position,
				m_moveSpeed,
				isEnd
			);

			//向きと速度
			m_direction = pathPos - oldPos;
			m_direction.Normalize();

			m_velocity += m_direction * m_moveSpeed * GameTime::GetInstance().GetFrameDeltaTime();

			//減速処理
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			m_direction = m_velocity;
			m_direction.Normalize();

			//速度がほぼ0ならば、0にする。
			if (fabsf(m_velocity.x + m_velocity.z) < 0.001f)
			{
				m_velocity.x = 0.0f;
				m_velocity.z = 0.0f;
			}

			//位置に速度を加算
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);

			//パスの位置にほぼ到達したら、
			if (m_moveSpeed == ENEMY_DASH_SPEED && (m_position - pathPos).Length() < ENEMY_DASH_SPEED
			|| (m_moveSpeed == ENEMY_WALK_SPEED) && (m_position - pathPos).Length() < ENEMY_WALK_SPEED)
			{
				m_position = pathPos;
			}

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

		void EnemyMove::FootStepsSE()
		{
			//足音の間隔
			m_footStepInterval--;

			if (m_footStepInterval < 0)
			{
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/EnemyFootStep.wav");	
				//プレイヤーとの距離から、音量を設定
				float dis = (m_enemy->GetEnemyMove()->GetPosition() - m_enemy->GetPlayer()->GetPlayerMove()->GetPosition()).Length();
				m_footStepVolume = max(0.01f, 1.0f - dis * 0.0003f);
				ss->SetVolume(m_footStepVolume);
				ss->Play(false);

				if (m_slowMoveFlag)
				{
					m_footStepInterval = ENEMY_SLOWWALK_FOOTSTEP_INTERVAL;
				}
				else if (m_enemy->GetEnemyState() == Enemy::enState_SearchPlayer)
				{
					m_footStepInterval = ENEMY_WALK_FOOTSTEP_INTERVAL;
				}
				else if (m_enemy->GetEnemyState() == Enemy::enState_Chase)
				{
					m_footStepInterval = ENEMY_DASH_FOOTSTEP_INTERVAL;
				}
				else
				{
					m_footStepInterval = ENEMY_SLOWWALK_FOOTSTEP_INTERVAL;
				}


			}

			if (m_velocity.Length() == 0.0f)
			{
				m_footStepInterval = ENEMY_SLOWWALK_FOOTSTEP_INTERVAL;
			}
		}
	}
}