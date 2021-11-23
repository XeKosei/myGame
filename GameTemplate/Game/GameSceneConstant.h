#pragma once
namespace nsHikageri
{
	namespace nsGameScene
	{


		namespace nsGameOverConstant
		{
			static const int INI_GAMEOVER_EXECUTE_COUNT = 650;	//ゲームオーバー画面実行中のカウント初期値
			static const int DISPLAY_SPRITE_TIMING = 500;	//スプライトを画面に表示するタイミング。
			static const int DELETE_SPRITE_TIMING = 100;	//スプライトの表示を消すタイミング
			
			static const float ADD_ALPHA_SPEED = 0.01f;	//スプライトのカラーにアルファ値を加算する速さ
			static const float MAX_GAMEOVER_SPRITE_ALPHA = 1.0f;	//ゲームオーバー表示のカラーの最大アルファ値
		
		}
	}
}