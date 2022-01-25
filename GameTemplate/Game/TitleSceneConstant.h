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

			static const float BLINKING_COLOR_ADD_SPEED = 0.008f;	//点滅の速さ
			static const float BLINKING_MIN_COLOR = 0.6f;	//点滅の最大カラー

			static const float TITLESPRITE_DELETE_SPEED = 0.02f;	//タイトル画面をじわじわ消す速さ
			static const float TITLESPRITE_DELETE_MAX_COLOR = 2.0f;	//タイトル画面を消すときの最初の色

			static const Vector2 SYNOPSISFONT_POS = {-320.0f, 260.0f};	//あらすじの表示位置
			static const float SYNOPSISFONT_SCALE = 0.7f;	//あらすじフォントの大きさ
			static const float SYNOPSISFONT_COLOR_ADD_SPEED = 0.02f;	//あらすじの表示の速さ

			static const float BLACKSPRITE_DELETE_SPEED = 0.05f;	//黒背景を消す速さ

			static const std::wstring SYNOPSIS =
			{
				L"\n"
				L"\n"
				L"目を覚ますと、そこは謎の部屋\n"
				L"\n"
				L"持っているのは、見知らぬ懐中電灯のみ\n"
				L"\n"
				L"まずは辺りを調べてみよう...\n"
				L"\n"
				L"\n"
				L"\n"
				L"              - 操作 -              \n"
				L"\n"
				L"     R1ボタン : 懐中電灯のスイッチ\n"
				L"\n"
				L"     L1ボタン :      走る\n"
				L"\n"
				L"     X ボタン : アイテムの使用\n"
				L"\n"
				L"                                              Loading...\n"
			};
		}
	}
}