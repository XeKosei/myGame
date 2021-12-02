#pragma once
namespace nsHikageri
{
	namespace nsGimmick
	{
		namespace nsChandelierConstant
		{
			static const float CHANDELIER_FORCE_RANGE = 1000.0f;	//シャンデリアの力が及ぶ範囲
			static const int CHANDELIER_ADD_STRESS_SPEED = 1;	//シャンデリアの光がエネミーにストレスを与える速さ
		}

		namespace nsChandelierManagerConstant
		{
			static const int CHANDELIER_NUM = 8;					//シャンデリアの数
			static const Vector3 CHANDELIER_SPOTLIGHT_COLOR = {3.0f,3.0f,3.0f};	//シャンデリアの光の色
			static const float CHANDELIER_SPOTLIGHT_RANGE = 10000.0f;	//スポットライトの光の範囲
			static const float CHANDELIER_SPOTLIGHT_ANGLE = 1.5f;		//シャンデリアの光の射出角度
		}

		namespace nsDoorConstant
		{
			static const float DOOR_OPEN_SPEED = 0.05f;	//ドアが開閉する速さ
			static const float MAX_DOOR_OPNE_ANGLE = 1.4;	//ドアが開く最大角度

			static const int INI_DOOR_CANNOTOPEN_EXECUTECOUNT = 30;	//ドアが開かない処理のカウント
			static const float DOOR_CANNOTOPNE_MOVESPEED = 0.01f;	//開かない動きの速さ
			static const float MAX_CANNOTOPEN_ADDANGLE = 0.02f;	//開かない動きの最大角度
		}
		namespace nsEyeWallConstant
		{
			static const int INI_DESAPPER_INTERVAL = 30;	//消え始めるまでのインターバル
			static const float DISAPPER_SPEED = 0.000001f;	//消える速さ
			static const float DISAPPER_SPEED_MUL_VALUE = 0.3f;	//消える速さにかける値	
		}
	}
}