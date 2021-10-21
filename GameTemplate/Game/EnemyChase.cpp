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
			//Move();//(仮)
			Chase();
			Turn();
		}

		void EnemyChase::Chase()
		{
			//ターゲットの位置
			m_targetPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
			//ターゲットとエネミーとのベクトルを計算。
			m_velocity = m_targetPos - m_position;

			//距離が一定以内まで縮まったら、攻撃に移行。
			if (m_velocity.Length() <= ENEMY_CAN_ATTACK_DIS)
			{
				m_enemy->SetEnemyState(Enemy::enState_Attack);
				//プレイヤーを噛みつかれ状態に
				m_enemy->GetPlayer()->SetPlayerState(nsPlayer::Player::enState_Bitten);
				m_enemy->GetPlayer()->GetPlayerBitten()->SetBittenState(nsPlayer::PlayerBitten::enBittenState_PreBitten);
				m_enemy->GetPlayer()->GetPlayerBitten()->SetEnemy(m_enemy);
			}

			//移動処理
			m_velocity.Normalize();
			m_velocity *= ENEMY_WALK_SPEED;
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

			if ((m_position - m_targetPos).Length() < 5.0f)
			{
				m_position = m_targetPos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
			}

			else {
				//位置を設定する。
				m_enemy->GetEnemyModel()->SetPosition(m_position);
			}
		}

		void EnemyChase::Turn()
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

		void EnemyChase::Move()
		{
			Vector3 toPassPointDir[2];
			toPassPointDir[0] = m_passPoint[1] - m_passPoint[0];
			toPassPointDir[0].Normalize();
			Vector3 passToPlayerDir[2];
			passToPlayerDir[0] = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_passPoint[0];
			passToPlayerDir[0].Normalize();

			toPassPointDir[1] = m_passPoint[0] - m_passPoint[1];
			toPassPointDir[1].Normalize();
			passToPlayerDir[1] = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_passPoint[1];
			passToPlayerDir[1].Normalize();
			
			if (Dot(toPassPointDir[0], passToPlayerDir[0]) >= 0 && Dot(toPassPointDir[1], passToPlayerDir[1]) >= 0
				&& (m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_position).Length() <= 500.0f)
				{
					m_targetPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
				}
			else if (Dot(toPassPointDir[0], passToPlayerDir[0]) >= 0 && Dot(toPassPointDir[1], passToPlayerDir[1]) >= 0
				&& (Dot(toPassPointDir[0], passToPlayerDir[0]) >= 0.95f
					|| Dot(toPassPointDir[1], passToPlayerDir[1]) >= 0.95f))
			{
				float dot = -1.0f;

				for (int i = 0; i < 2; i++)
				{
					Vector3 toPlayerDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_position;
					toPlayerDir.Normalize();
					Vector3 toPassPointDir = m_passPoint[i] - m_position;
					toPassPointDir.Normalize();

					if (Dot(toPlayerDir, toPassPointDir) >= dot)
					{
						dot = Dot(toPlayerDir, toPassPointDir);
						m_targetPos = m_passPoint[i];
					}
				}
			}
			else
			{
				m_targetPos = m_passPoint[0];
				float dis = (m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_passPoint[0]).Length();

				for (int i = 0; i < 2; i++)
				{
					Vector3 toPlayerDis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_passPoint[i];

					if ((toPlayerDis).Length() <= dis)
					{
						dis = (toPlayerDis).Length();
						m_targetPos = m_passPoint[i];
					}
				}
			}
			

			
		}
	}
}