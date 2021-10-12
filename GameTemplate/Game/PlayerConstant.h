#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const float PLAYER_MODEL_WIDTH = 50.0f;	//プレイヤーのモデルの横幅
			static const float PLAYER_MODEL_HEIGHT = 100.0f;	//プレイヤーのモデルの高さ
		}
		//Playerクラスで利用する定数
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 3.0f;	//プレイヤーの歩く速さ
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 1.5f;//プレイヤーの走る速さ
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//プレイヤーが動くときの摩擦
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//落下スピード
			static const float GRAVITY_INDEX = 1.2f;		//落下スピードにかける指数
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 0.05f;		//カメラが動く速さ
			static const float PLAYER_EYES_HEIGHT = 200.0f;		//プレイヤーの目の高さ
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//カメラのターゲットへの距離
		}

	}
}
