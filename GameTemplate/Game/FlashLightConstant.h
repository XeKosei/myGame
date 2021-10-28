#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 INI_FLASHLIGHT_COLOR = { 30.0f,30.0f,30.0f };	//懐中電灯の初期カラー
			static const float INI_FLASHLIGHT_RANGE = 3000.0f;					//懐中電灯の初期影響範囲
			static const float INI_FLASHLIGHT_ANGLE = 0.5f;					//懐中電灯の初期射出角度
			static const Vector3 APPLY_FLASHLIGHT_POS_VALUE = { 1.8f, 0.8f, 3.0f };	//懐中電灯の位置を計算するための値
			static const int TO_SPOTLIGHTCAMERA_TARGET_DIS = 100;				//スポットライトの注視点までの距離
		}

		namespace nsFlashLightActionConstant
		{
			static const float FLASHLIGHT_ANGLE_ADJUST_SPEED = 0.01f;	//懐中電灯の射出角度を調節する速度
		}

		namespace nsAbilityStrobeFlash
		{
			static const int INI_STROBEFLASH_CHARGE_COUNT = 50;	//ストロボフラッシュのチャージ時間の初期値
			static const Vector3 INI_STROBEFLASH_COLOR = {150.0f,150.0f,150.0f};	//ストロボフラッシュの明るさの初期値
			static const Vector3 STROBEFLASH_COLOR_DECREASE_SPEED = {1.5f,1.5f,1.5f};	//ストロボフラッシュの明るさが下がる速さ
		}

		namespace nsFlashLightBattery
		{
			static const float MAX_BATTERY_LEVEL = 100.0f;	//最大バッテリー残量
			static const float BATTERY_LEVEL_DECREASE_SPEED = 0.001f; //バッテリーの減る速度
 
		}
	}
}