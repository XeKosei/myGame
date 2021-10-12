#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerConstant.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerMoveConstant;

		bool PlayerMove::Start()
		{
			return true;
		}

		//Player.cppのUpdate()で呼び出す処理
		void PlayerMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void PlayerMove::Move()
		{
			//Bボタンが押されていたら、前方にのみダッシュできる。
			if (g_pad[0]->IsPress(enButtonB) && g_pad[0]->GetLStickYF() >= 0.77f)
			{
				m_plMoveSpeed = PLAYER_DASH_SPEED;
			}
			else
			{
				m_plMoveSpeed = PLAYER_WALK_SPEED;
			}

			//スティックの傾きからプレイヤーの速度を計算
			Vector3 xSpeed = g_camera3D->GetRight() * g_pad[0]->GetLStickXF();
			Vector3 ySpeed = Cross(g_camera3D->GetRight(), Vector3::AxisY) * g_pad[0]->GetLStickYF();
			m_velocity += (xSpeed + ySpeed) * m_plMoveSpeed;

			//減速処理
			m_velocity.x -= m_velocity.x * PLAYER_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * PLAYER_MOVE_FRICTION;

			//プレイヤーを上下に動かす
			if (g_pad[0]->IsTrigger(enButtonRB2))
				m_velocity.y += 30.0f;
			if (g_pad[0]->IsTrigger(enButtonLB2))
				m_velocity.y -= 30.0f;

			//重力
			if (m_player->GetCharaCon()->IsOnGround() == false) 
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
			m_position = m_player->GetCharaCon()->Execute(m_velocity, 1.0f);
			//m_position += m_velocity;
			//位置を設定する。
			m_player->SetPosition(m_position);
		}

		void PlayerMove::Turn()
		{
			if (g_pad[0]->IsPress(enButtonLB1) == false)
			{
				//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
				//cameraDir.x / cameraDir.zの結果はtanθになる。
				//atan2を使用して、角度を求めている。
				//これが回転角度になる。
				Vector3 cameraDir = g_camera3D->GetForward();
				cameraDir.y = 0.0f;
				float angle = atan2(cameraDir.x, cameraDir.z);
				//atanが返してくる角度はラジアン単位なので
				//SetRotationDegではなくSetRotationを使用する。
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_player->SetRotation(m_qRot);
			}
		}
	}
}