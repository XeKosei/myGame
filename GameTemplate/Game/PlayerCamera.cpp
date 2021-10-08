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
			return true;
		}

		void PlayerCamera::ExecuteUpdate()
		{
			//Rスティックの傾きを取得
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();

			//Rスティックの傾きから、カメラの向きを計算。
			m_cameraDir += g_camera3D->GetRight() * x * CAMERA_MOVE_SPEED;
			m_cameraDir += g_camera3D->GetUp() * y * CAMERA_MOVE_SPEED;
			m_cameraDir.Normalize();

			//カメラの位置を計算する。
			m_cameraPos = m_player->GetPosition();
			//カメラの位置を、プレイヤーの目の高さにする。
			m_cameraPos.y += PLAYER_EYES_HEIGHT;
			//カメラの位置から、カメラの向いている方向に一定以上向かった位置を注視点として設定する。
			Vector3 cameraTarget = m_cameraPos + m_cameraDir * TO_CAMERA_TARGET_DIS;

			g_camera3D->SetPosition(m_cameraPos);
			g_camera3D->SetTarget(cameraTarget);
			
		}
	}
}