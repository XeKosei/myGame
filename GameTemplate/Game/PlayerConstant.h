#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		//Playerクラスで利用する定数
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_MOVE_SPEED = 15.0f;	//プレイヤーが動く速さ
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 0.05f;		//カメラが動く速さ
			static const float PLAYER_EYES_HEIGHT = 200.0f;		//プレイヤーの目の高さ
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//カメラのターゲットへの距離
		}

	}
}
