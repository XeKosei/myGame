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

		void PlayerMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void PlayerMove::Move()
		{
			//スティックの傾きからプレイヤーの速度を計算
			Vector3 xSpeed = g_camera3D->GetRight() * g_pad[0]->GetLStickXF();
			Vector3 ySpeed = Cross(g_camera3D->GetRight(), Vector3::AxisY) * g_pad[0]->GetLStickYF();
			m_velocity = (xSpeed + ySpeed) * PLAYER_MOVE_SPEED;

			//プレイヤーを上下に動かす
			m_velocity.y = 0.0f;

			if (g_pad[0]->IsPress(enButtonRB2))
				m_velocity.y += 10.0f;
			if (g_pad[0]->IsPress(enButtonLB2))
				m_velocity.y -= 10.0f;

			//位置に速度を加算
			m_position += m_velocity;
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