#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 INI_FLASHLIGHT_COLOR = { 3.0f,3.0f,3.0f };	//懐中電灯の初期カラー
			static const float INI_FLASHLIGHT_RANGE = 10000.0f;					//懐中電灯の初期影響範囲
			static const float INI_FLASHLIGHT_ANGLE = 1.0f;					//懐中電灯の初期射出角度
			static const Vector3 INI_FLASHLIGHT_MODEL_SCALE = { 1.5f,1.5f,1.5f };	//懐中電灯のモデルのスケール
			static const Vector3 FLASHLIGHT_MODEL_POS_APPLY_VALUE = { 1.8f, -1.2f, 3.0f };	//懐中電灯のモデルの位置を計算するための値
			static const Vector3 FLASHLIGHT_POS_APPLY_VALUE = { 50.0f, -20.0f, 0.0f };	//懐中電灯の本当の位置を計算するための値
			static const int TO_SPOTLIGHTCAMERA_TARGET_DIS = 100;				//スポットライトの注視点までの距離
		}

		namespace nsFlashLightActionConstant
		{
			static const float FLASHLIGHT_ANGLE_ADJUST_SPEED = 0.01f;	//懐中電灯の射出角度を調節する速度
		}

		namespace nsFlashLightBatteryConstant
		{
			static const float MAX_BATTERY_LEVEL = 100.0f;	//最大バッテリー残量
			static const float BATTERY_LEVEL_DECREASE_SPEED = 0.01f; //バッテリーの減る速度
		}

		namespace nsAbilityStrobeFlashConstant
		{
			static const int INI_STROBEFLASH_CHARGE_COUNT = 100;	//ストロボフラッシュのチャージ時間の初期値
			static const Vector3 INI_STROBEFLASH_COLOR = {50.0f,50.0f,50.0f};	//ストロボフラッシュの明るさの初期値
			static const Vector3 STROBEFLASH_COLOR_DECREASE_SPEED = {1.0f,1.0f,1.0f};	//ストロボフラッシュの明るさが下がる速さ
			static const float INI_STROBEFLASH_BATTERY_COST = 20.0f;	//ストロボフラッシュで消費するバッテリーのコスト
		}

		namespace nsAbilityClairvoyanceConstant
		{
			static const float INI_CRAIRVOYANCE_BATTERY_COST = 0.05f;	//クレアボヤンスで消費するバッテリー(発動中毎フレーム)
		}

		namespace nsAbilityMedousaEyeConstant
		{
			static const int INI_MEDOUSAEYEFLASH_CHARGE_COUNT = 50;	//メドゥーサアイのチャージ時間の初期値
			static const Vector3 INI_MEDOUSAEYEFLASH_COLOR = { 50.0f,50.0f,50.0f };	//ストロボフラッシュの明るさの初期値
			static const float  INI_MEDOUSAEYEFLASH_BATTERY_COST = 20.0f;	//メドゥーサアイで消費するバッテリーのコスト
		}
	}
}