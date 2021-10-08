#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		namespace nsFlashLightConstant
		{
			static const Vector3 FLASHLIGHT_INI_COLOR = { 10.0f,10.0f,10.0f };	//懐中電灯の初期カラー
			static const float FLASHLIGHT_INI_RANGE = 2000.0f;					//懐中電灯の初期影響範囲
			static const float FLASHLIGHT_INI_ANGLE = Math::DegToRad(50.0f);	//懐中電灯の初期射出角度
			static const Vector3 PLAYER_HAND_POS = { 5.0f, 100.0f, 5.0f };
		}
	}
}