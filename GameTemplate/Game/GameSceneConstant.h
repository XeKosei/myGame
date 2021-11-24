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

		namespace nsGameClearConstant
		{
			static const int INI_GAMECLEAR_EXECUTE_COUNT = 1300;	//ゲームクリア画面実行中のカウント初期値
			static const int DISPLAY_TITLENAME_TIMING = 1050;	//タイトル名を画面に表示するタイミング。
			static const int DELETE_TITLENAME_TIMING = 700;	//タイトル名の表示を消すタイミング
			static const int DISPLAY_CLEARFONT_TIMING = 600;	//クリアフォントを表示するタイミング
			static const int DELETE_CLEARFONT_TIMING = 300;	//クリアフォントを消すタイミング
			static const int DELETE_GAMESCENE_TIMING = 1200;	//ゲームシーンを消すタイミング

			static const float WHITESPRITE_ADD_SPEED = 0.01f;	//白スプライトを表示する速さ
			static const float TITLENAME_DELETE_SPEED = 0.01f;	//タイトル名の表示を消す速さ
			static const float CLEARFONT_ADD_SPEED = 0.02f;	//クリアフォントを表示する速さ
		
			static const Vector2 CLEARFONT_POS = { -250.0f, 50.0f };	//クリアフォントの表示位置
		}
	}
}