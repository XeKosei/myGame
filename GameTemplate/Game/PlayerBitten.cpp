#include "stdafx.h"
#include "Playerinclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerBittenConstant;

		PlayerBitten::~PlayerBitten()
		{

		}

		bool PlayerBitten::Start()
		{
			m_bittenStates = enBittenState_PreBitten;
			//動けるようになるまでのインターバルを設定。
			m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
			return true;
		}
		void PlayerBitten::ExecuteUpdate()
		{
			switch (m_bittenStates)
			{
			case enBittenState_PreBitten:
				PreBitten();
				break;
			case enBittenState_Bitten:
				Bitten();
				break;
			case enBittenState_EndBitten:
				EndBitten();
				break;
			default:
				break;
			}

			//敵の状態が噛みつきではなくなったら、
			if (m_enemy->GetEnemyState() != nsEnemy::Enemy::enState_Attack)
			{
				m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
				SetBittenState(enBittenState_PreBitten);
				m_player->SetInvincible(200);
			}
		}
		void PlayerBitten::PreBitten()
		{
			//プレイヤーのカメラの向きを設定。
			Vector3 toEnemyDir = m_enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head") - m_player->GetPlayerCamera()->GetCameraPos();
			toEnemyDir.Normalize();
			Vector3 cameraDir = m_player->GetPlayerCamera()->GetDirection();
			//エネミーへの向きと、カメラの向きで内積を取る。
			float dot = Dot(toEnemyDir, cameraDir);

			//内積の結果によって、カメラの動きが変化
			Vector3 dir = m_player->GetPlayerCamera()->GetDirection();
			//向きがほぼ同じなら、同じにする。
			if (dot >= 0.99f)
			{
				dir = toEnemyDir;
			}
			//0以上なら、滑らかに相手に振り向く
			else if(dot >= 0)
			{				
				dir += (toEnemyDir - cameraDir) * CAMERA_TURN_SPEED;
			}
			//0以下なら、まずカメラを左右に回転させる。
			else
			{
				Vector3 enemyRight = Cross(toEnemyDir, Vector3::AxisY);
				//右を向く方が早いなら右を向く
				if (Dot(enemyRight, cameraDir) >= 0)
				{
					dir += m_player->GetPlayerCamera()->GetCameraRight() * CAMERA_TURN_SPEED;
				}
				//左を向く方が早いなら左を向く
				else
				{
					dir += m_player->GetPlayerCamera()->GetCameraRight() * -CAMERA_TURN_SPEED;
				}
			}

			m_player->GetPlayerCamera()->SetCameraDir(dir);

			//モデルの向きを設定。
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);

			//エネミーの噛みつきが次のステップへ移行したら、プレイヤーも次のステップへ移行
			if (m_enemy->GetEnemyAttack()->GetBiteState() == nsEnemy::EnemyAttack::enBiteState_Bite)
			{
				SetBittenState(enBittenState_Bitten);
			}
		}
		void PlayerBitten::Bitten()
		{
			//BボタンかAボタン連打で抵抗する。
			if (g_pad[0]->IsTrigger(enButtonB) || g_pad[0]->IsTrigger(enButtonA))
			{
				m_enemy->GetEnemyAttack()->RegistToBite(RESIST_TO_BITE_NUM);
			}

			//エネミーの噛みつきが次のステップへ移行したら、プレイヤーも次のステップへ移行
			if (m_enemy->GetEnemyAttack()->GetBiteState() == nsEnemy::EnemyAttack::enBiteState_EndBite)
			{
				SetBittenState(enBittenState_EndBitten);
			}

			//プレイヤーカメラとモデルの向きを設定。
			Vector3 dir = m_enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head") - m_player->GetPlayerCamera()->GetCameraPos();
			dir.Normalize();
			m_player->GetPlayerCamera()->SetCameraDir(dir);

			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);
		}
		void PlayerBitten::EndBitten()
		{
			//動けるようになるまでのインターバル
			m_canMoveInterval--;
			//インターバルが終わったら、リセットして、動けるようになる。
			if (m_canMoveInterval <= 0)
			{
				m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
				SetBittenState(enBittenState_PreBitten);
				m_player->SetInvincible(200);
			}
		}

	}
}