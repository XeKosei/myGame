#include "stdafx.h"
#include "PlayerCamera.h"
#include "Player.h"
#include "PlayerConstant.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerCameraConstant;

		bool PlayerCamera::Start()
		{
			m_plEyeHeight = INI_PLAYER_EYE_HEIGHT;
			return true;
		}

		//Player.cppのUpdate()で呼び出す処理
		void PlayerCamera::ExecuteUpdate()
		{
			//前フレームのカメラの位置を取得
			Vector3 oldCameraDir = m_cameraDir;

			//Rスティックの傾きを取得
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();

			//Rスティックの傾きから、カメラの向きを計算。
			m_cameraDir += g_camera3D->GetRight() * x * CAMERA_MOVE_SPEED;
			m_cameraDir += g_camera3D->GetUp() * y * CAMERA_MOVE_SPEED;
			m_cameraDir.Normalize();

			//カメラが上か下に向きすぎた場合、それ以上は上下に向かないようにする。
			if (m_cameraDir.y >= 0.9f || m_cameraDir.y <= -0.9f)
			{
				m_cameraDir.y = oldCameraDir.y;
			}

			//簡易クイックターン(仮で)
			if (g_pad[0]->IsTrigger(enButtonB) && g_pad[0]->GetLStickYF() < -0.8f)
			{
				m_cameraDir.x *= -1.0f;
				m_cameraDir.z *= -1.0f;
				m_cameraDir.y = 0.0f;
			}

			//カメラの位置を計算する。
			m_cameraPos = m_player->GetPosition();
			//カメラの位置を、プレイヤーの目の高さにする。
			m_cameraPos.y += m_plEyeHeight;
			//カメラの位置から、カメラの向いている方向に一定以上向かった位置を注視点として設定する。
			Vector3 cameraTarget = m_cameraPos + m_cameraDir * TO_CAMERA_TARGET_DIS;

			g_camera3D->SetPosition(m_cameraPos);
			g_camera3D->SetTarget(cameraTarget);
				
			g_camera3D->Update();
		}
	}
}