#pragma once
namespace nsHikageri
{
	namespace nsTitleScene
	{
		namespace nsTitleSceneConstant
		{
			static const Vector2 TITLEFONT_POS = { -150.0f, -200.0f };	//タイトルフォントの位置
			static const float TITLEFONT_SCALE = 0.7f;	//タイトルフォントの大きさ
			static const int SECOND_MOVE_INTERVAL = 20;	//SecondMoveに移行するまでの間隔

			static const float TITLESPRITE_COLOR_ADD_SPEED = 0.03f;	//タイトル画面を表示する速さ
			static const float TITLEFONT_COLOR_ADD_SPEED = 0.03f;	//タイトル画面の文字を表示する速さ

			static const float BLINKING_COLOR_ADD_SPEED = 0.005f;	//点滅の速さ
			static const float BLINKING_MIN_COLOR = 0.7f;	//点滅の最大カラー

			static const float TITLESPRITE_DELETE_SPEED = 0.02f;	//タイトル画面をじわじわ消す速さ
			static const float TITLESPRITE_DELETE_MAX_COLOR = 2.0f;	//タイトル画面を消すときの最初の色

			static const Vector2 SYNOPSISFONT_POS = {-200.0f, 250.0f};	//あらすじの表示位置
			static const float SYNOPSISFONT_SCALE = 0.7f;	//あらすじフォントの大きさ
			static const float SYNOPSISFONT_COLOR_ADD_SPEED = 0.02f;	//あらすじの表示の速さ

			static const float BLACKSPRITE_DELETE_SPEED = 0.05f;	//黒背景を消す速さ
		}
	}
}