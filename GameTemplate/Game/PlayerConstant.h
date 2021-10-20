#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const Vector3 INI_PLAYER_POSITION = { 1000.0f,0.0f,0.0f };	//プレイヤーの初期位置
			static const float PLAYER_MODEL_WIDTH = 10.0f;	//プレイヤーのモデルの横幅
			static const float PLAYER_MODEL_HEIGHT = 20.0f;	//プレイヤーのモデルの高さ
			static const Vector3 INI_PLAYER_SCALE = { 1.0f, 1.0f, 1.0f };	//プレイヤーのモデルの大きさの初期値
		}
		//Playerクラスで利用する定数
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 150.0f;	//プレイヤーの歩く速さ
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 1.5f;//プレイヤーの走る速さ
			static const float PLAYER_CROUCHDOWN_WALK_SPEED = PLAYER_WALK_SPEED / 2.0f;//プレイヤーの屈み歩きの速さ
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//プレイヤーが動くときの摩擦
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//落下スピード
			static const float GRAVITY_INDEX = 1.2f;		//落下スピードにかける指数
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 3.0f;		//カメラが動く速さ
			static const float INI_PLAYER_EYE_HEIGHT = 200.0f;		//プレイヤーの目の高さ
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//カメラのターゲットへの距離
		}

		namespace nsPlayerActionConstant
		{
			static const float CROUCHDOWN_PLAYER_EYE_HEIGHT = 100.0f;		//プレイヤーが屈んでいる時の目の高さ
			static const Vector3 CROUCHDOWN_PLAYER_SCALE = { 1.0f, 0.5f, 1.0f };	//プレイヤーのモデルの大きさの初期値
		}

		namespace nsPlayerHPConstant
		{
			static const float MAX_PLAYER_HP = 100.0f;	//プレイヤーの体力の最大値
			static const int DAMAGE_INTERVAL = 20;	//次にダメージを受けられるようになるまでの間隔
		}
	}
}
