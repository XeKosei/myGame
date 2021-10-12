#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 FLASHLIGHT_INI_COLOR = { 10.0f,10.0f,10.0f };	//懐中電灯の初期カラー
			static const float FLASHLIGHT_INI_RANGE = 5000.0f;					//懐中電灯の初期影響範囲
			static const float FLASHLIGHT_INI_ANGLE = Math::DegToRad(50.0f);	//懐中電灯の初期射出角度
			static const Vector3 APPLY_FLASHLIGHT_POS_VALUE = { 1.8f, 0.8f, 3.0f };	//懐中電灯の位置を計算するための値
			static const int TO_SPOTLIGHTCAMERA_TARGET_DIS = 100;				//スポットライトの注視点までの距離
		}
	}
}