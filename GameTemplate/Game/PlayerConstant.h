#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const Vector3 INI_PLAYER_POSITION = { 1000.0f, 0.0f,0.0f };	//プレイヤーの初期位置
			static const float PLAYER_MODEL_WIDTH = 50.0f;	///:プレイヤーのモデルの横幅
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

			static const float FOOTSTEP_SE_INTERVAL = 200;	//足音の間隔
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
			
			static const float BIG_DAMAGE_LINE = MAX_PLAYER_SANITY / 3;	//大ダメージを受けていると判断されるライン

			static const float DARKNESS_SANITY_DAMAGE_SPEED = 0.05f;	//暗い時にSAN値がじわじわと減っていくスピード
		
			static const float BLOODSPRITE_DEC_SPEED = 0.02f;	//ダメージ時のスプライトの消える速さ
			static const float MAX_BLOODSPRITE_COLOR = 2.0f;	//ダメージ時のスプライトの最大カラー
		}

		namespace nsPlayerBittenConstant
		{
			static const int INI_CAN_MOVE_INTERVAL = 30;	//動けるようになるまでのインターバル
			static const int RESIST_TO_BITE_NUM = 100;	//噛みつきに抵抗する数値	
			static const float CAMERA_TURN_SPEED = 0.2f;	//カメラが振り向く速さ
		}

		namespace nsPlayerPouchConstant
		{
			static const int TRANQUILIZER_RECOVERY_NUM = 50.0f;	//精神安定剤を使った時の回復量
		}

		namespace nsPlayerTargetConstant
		{
			static const float CATCH_EYES_DIS = 400.0f;	//オブジェクトがプレイヤーの目を引く距離
			static const float CATCH_EYES_DOT = 0.95f;	//オブジェクトがプレイヤーの目を引く内積
			static const Vector2 ITEMNAME_FONT_POS = {-50.0f,-200.0f};	//アイテム名の表示位置
			static const float ITEMNAME_FONT_SCALE = 0.65f;	//アイテム名のフォントの大きさ
			
			//ターゲットの名前
			static const std::wstring TARGET_NAME[PlayerTarget::enTarget_num] = { 
				L"", L"A ドア", L"A 鍵", L"A 懐中電灯の部品", 
				L"A 精神安定剤",L"A 電池", L"A 紙"};
			
			//コマンド表示
			static const std::wstring COMMAND_TEXT[PlayerTarget::enCommand_num] = {L"", L"A:拾う",L"A:開ける",L"A:閉める", L"A:読む"};
			
			static const Vector2 COMMAND_FONT_POS = { 400.0f, -250.0f };	//コマンドフォントの位置
		}

		namespace nsPlayerReadConstant
		{
			static const float ADD_BLACKSPRITE_COLOR_SPEED = 0.05f;	//画面を暗くする速さ
			static const float MAX_BLACKSPRITE_COLOR = 0.5f;	//黒スプライトの最大カラー
		}

		namespace nsPlayerUIConstant
		{
			/////////////////////////////HazySprite関連
			static const Vector4 INI_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 0.0f };	//Hazyスプライトの初期カラー
			static const Vector4 DAMAGED_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };	//ダメージを受けた際のHazyスプライトのカラー
			static const float HAZYSPRITE_MUL_COLOR_PINCH = 20.0f;	//ピンチ時にHazyスプライトのカラーに掛ける値

			static const float MUL_HAZYSPRITE_COLOR_VALUE = 1.5f;	//HazySpriteのカラーにかける値

			static const float ADD_ALPHA_SPEED = 0.001f;	//スプライトが点滅する速さ
			static const float MAX_ADD_ALPHA = 0.02f;		//点滅の最大加算値
			static const float MIN_ADD_ALPHA = -0.02f;		//点滅の最小加算値

			static const float DYING_ADD_ALPHA_SPEED = 0.5f;	//死んだときのアルファ値加算の速さ
			static const float DYING_MAX_ADD_ALPHA = 100.0f;	//死んだときのアルファ値の最大加算値
				
			///////////////////////////////ポーチアイテム関連
			static const Vector2 INI_ITEMFONT_POS = { -550.0f, -285.0f };	//ポーチアイテムのフォントの位置
			static const float INI_ITEMFONT_SCALE = 0.55f;	//ポーチアイテムのフォントのスケール
			static const Vector2 INI_ITEMNUMFONT_POS = { -425.0f, -285.0f };	//ポーチアイテムの数の表示位置
			static const float INI_ITEMNUMFONT_SCALE = 0.6f;	//アイテム数のフォントのスケール

			//アイテム名
			static const std::wstring ITEM_NAME[PlayerPouch::enItem_num] = {
				L"   電池   ", L"精神安定剤" , L" 赤色の鍵", L" 青色の鍵", L" 緑色の鍵",
				L" 黄色の鍵", L" 紫色の鍵", L" 最後の鍵" };

			//アイテムアイコンのスプライトのファイルパス
			static const char* ITEMSPRITE_FILEPATH[PlayerPouch::enItem_num] = {
				"Assets/Image/BatteryIcon.DDS",
				"Assets/Image/TranquilizerIcon.DDS",
				"Assets/Image/RedKeyIcon.DDS",
				"Assets/Image/BlueKeyIcon.DDS",
				"Assets/Image/GreenKeyIcon.DDS",
				"Assets/Image/YellowKeyIcon.DDS",
				"Assets/Image/PurpleKeyIcon.DDS",
				"Assets/Image/WhiteKeyIcon.DDS"
			};
			static const Vector3 INI_ITEMSPRITE_POS = {-490.0f, -260.0f, 0.0f};	//アイテムアイコンの位置
			static const Vector3 INI_ITEMSPRITE_SCALE = {0.2f,0.2f,0.2f};	//アイテムアイコンの大きさ

			///////////////////////////////バッテリー関連
			static const Vector3 INI_BATTERYSPRITE_POS = { 540.0f, 285.0f , 0.0f };	//バッテリー表示の位置
			static const Vector3 INI_BATTERYSPRITE_SCALE = { 0.3f,0.3f,0.3f };	//バッテリー表示の初期スケール
			
			//バッテリー表示を変えるライン
			static const float BATTERYSPRITE_CHANGE_LINE[PlayerUI::enBatteryDispTypes_num] = 
			{0.0f,0.0f,25.0f,50.0f,75.0f};

			//バッテリースプライトのファイルパス
			static const char* BATTERYSPRITE_FILEPATH[PlayerUI::enBatteryDispTypes_num] = {
				"Assets/Image/Battery0.DDS",
				"Assets/Image/Battery1.DDS",
				"Assets/Image/Battery2.DDS",
				"Assets/Image/Battery3.DDS",
				"Assets/Image/Battery4.DDS"
			};

			static const float BATTERY_UI_DELETE_SPEED = 0.05f;	//バッテリーUIを消す速さ
		}
	}
}
