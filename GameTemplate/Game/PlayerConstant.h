#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const Vector3 INI_PLAYER_POSITION = { 1000.0f,0.0f,0.0f };	//プレイヤーの初期位置
			static const float PLAYER_MODEL_WIDTH = 10.0f;	//プレイヤーのモデルの横幅
			static const float PLAYER_MODEL_HEIGHT = 120.0f;	//プレイヤーのモデルの高さ
			static const Vector3 INI_PLAYER_SCALE = { 1.0f, 1.0f, 1.0f };	//プレイヤーのモデルの大きさの初期値
		}
		//Playerクラスで利用する定数
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 80.0f;	//プレイヤーの歩く速さ
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 2.0f;//プレイヤーの走る速さ
			static const float PLAYER_CROUCHDOWN_WALK_SPEED = PLAYER_WALK_SPEED / 2.0f;//プレイヤーの屈み歩きの速さ
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//プレイヤーが動くときの摩擦
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//落下スピード
			static const float GRAVITY_INDEX = 1.2f;		//落下スピードにかける指数
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 3.0f;		//カメラが動く速さ
			static const float INI_PLAYER_EYE_HEIGHT = 250.0f;		//プレイヤーの目の高さ
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//カメラのターゲットへの距離

			static const float ADD_EYEHEIGHT_SPEED_IDLE = 0.02f;	//カメラが呼吸で上下する速さ
			static const float MAX_ADD_EYEHEIGHT = 2.0f;	//カメラが呼吸で上下する最大加算値
			static const float MIN_ADD_EYEHEIGHT = -2.0f;	//カメラが呼吸で上下する最小加算値
		}

		namespace nsPlayerActionConstant
		{
			static const float CROUCHDOWN_PLAYER_EYE_HEIGHT = 100.0f;		//プレイヤーが屈んでいる時の目の高さ
			static const Vector3 CROUCHDOWN_PLAYER_SCALE = { 1.0f, 0.5f, 1.0f };	//プレイヤーのモデルの大きさの初期値
		}

		namespace nsPlayerSanityConstant
		{
			static const float MAX_PLAYER_SANITY = 100.0f;	//プレイヤーのSAN値の最大値
			static const int DAMAGE_INTERVAL = 200;	//次にダメージを受けられるようになるまでの間隔
			static const Vector4 INI_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 0.0f };	//Hazyスプライトの初期カラー
			static const Vector4 DAMAGED_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };	//ダメージを受けた際のHazyスプライトのカラー
			static const float HAZYSPRITE_MUL_COLOR_PINCH = 20.0f;	//ピンチ時にHazyスプライトのカラーに掛ける値

			static const float BIG_DAMAGE_LINE = MAX_PLAYER_SANITY / 3;	//大ダメージを受けていると判断されるライン

			static const float ADD_ALPHA_SPEED = 0.001f;	//スプライトが点滅する速さ
			static const float MAX_ADD_ALPHA = 0.02f;		//点滅の最大加算値
			static const float MIN_ADD_ALPHA = -0.02f;		//点滅の最小加算値
		}

		namespace nsPlayerBittenConstant
		{
			static const int INI_CAN_MOVE_INTERVAL = 30;	//動けるようになるまでのインターバル
			static const int RESIST_TO_BITE_NUM = 100;	//噛みつきに抵抗する数値

			
		}

		namespace nsPlayerPouchConstant
		{
			static const std::wstring ITEM_NAME[PlayerPouch::enItem_num] = { L"電池", L"精神安定剤" };

			static const int TRANQUILIZER_RECOVERY_NUM = 50.0f;	//精神安定剤を使った時の回復量
		}
	}
}
