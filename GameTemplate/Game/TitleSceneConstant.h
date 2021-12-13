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
				L"目を覚ますと、そこは見知らぬ部屋だった。\n"
				L"\n"
				L"ここはどこだろう。いつの間にこんな場所に?\n"
				L"\n"
				L"怪我などはないか自分の体を確認すると、\n"
				L"いつの間にか右手に知らない懐中電灯が\n"
				L"握られていることに気が付いた。\n"
				L"\n"
				L"辺りは薄暗くて、とても不安になる。\n"
				L"\n"
				L"とりあえず、まずはこの懐中電灯を使って\n"
				L"辺りを調べてみて、状況を把握しよう...\n"
				L"\n"
				L"              - 操作 -              \n"
				L"\n"
				L"      Rボタン:懐中電灯のスイッチ\n"
				L"      Lボタン:走る\n"
				L"      Xボタン:アイテムを使う\n"
				L"                                              Loading...\n"
			};
		}
	}
}