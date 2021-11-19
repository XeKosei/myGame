#pragma once
namespace nsHikageri
{
	namespace nsGimmick
	{
		namespace nsChandelierConstant
		{
			static const float CHANDELIER_LIGHT_RANGE = 10000.0f;	//シャンデリアの光の範囲
			static const int CHANDELIER_ADD_STRESS_SPEED = 1;	//シャンデリアの光がエネミーにストレスを与える速さ
		}

		namespace nsDoorConstant
		{
			static const float DOOR_OPEN_SPEED = 0.05f;	//ドアが開閉する速さ
			static const float MAX_DOOR_OPNE_ANGLE = 3.141592 / 2;	//ドアが開く最大角度(90度)
		}
		namespace nsEyeWallConstant
		{
			static const int INI_DESAPPER_INTERVAL = 30;	//消え始めるまでのインターバル
			static const float DISAPPER_SPEED = 0.000001f;	//消える速さ
			static const float DISAPPER_SPEED_MUL_VALUE = 0.3f;	//消える速さにかける値	
		}
	}
}