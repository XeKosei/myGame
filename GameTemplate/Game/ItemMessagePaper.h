#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsItem
	{
		class ItemMessagePaper : public IGameObject
		{
		public:
			//この紙に書かれている内容
			enum EnMessagePaperKinds
			{
				enMessagePaperKind_00,
				enMessagePaperKind_01,
				enMessagePaperKind_02,
				enMessagePaperKind_03,
				enMessagePaperKind_04,
				enMessagePaperKind_05,
				enMessagePaperKind_06,
				enMessagePaperKind_07,
				enMessagePaperKind_num
			};

			~ItemMessagePaper();
			bool Start();
			void Update();

			void ExecuteShineEffect();

			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			//読むときの処理
			void Read();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief 紙に書かれている内容を設定
			/// @param messagePaperText 設定する内容
			void SetMessagePaperText(EnMessagePaperKinds kind) { m_kind = kind; };
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_paperModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			EnMessagePaperKinds m_kind = enMessagePaperKind_00;

			//光るエフェクト
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
			bool m_shineEffPlayingFlag = false;
		};

		namespace nsItemMessagePaperConstant
		{
			static const std::wstring MESSAGEPAPAER_TEXT[ItemMessagePaper::enMessagePaperKind_num] =
			{
				//enMessagePaperKind_00
				L"これを誰かが読んでくれることを願う。\n"
				L"\n"
				L"俺の名前はダニエル\n"
				L"気が付くとこんな場所で倒れていた。\n"
				L"近くには、さっき拾った懐中電灯くらいしか\n"
				L"見当たらない。\n"
				L"\n"
				L"ここは不気味なほど真っ暗で、明かりが無いと\n"
				L"どんどん体力が失われていくのを感じる。\n"
				L"\n"
				L"それにさっきから変な呻き声が聞こえてくる。\n"
				L"もしかしたら誰かいるのかもしれない...\n"
				L"\n"
				L"仕方ねぇから、俺は少し先を見てこようと思う。\n"
				L"もし誰かいるのなら、一緒に出口を探してくれ!\n"
				,

				//enMessagePaperKind_01
				L"一体なんなんだあの化け物は!\n"
				L"こっちを見つけたら急に追いかけて来やがった!\n"
				L"\n"
				L"やられちまうかと思ったが、どうやら慌てて\n"
				L"逃げ込んだのがこの部屋で正解だったらしい。\n"
				L"\n"
				L"どうやら奴は強い光が苦手なようだ。\n"
				L"とは言ってもこの懐中電灯の光くらいなら\n"
				L"平気なようだが...\n"
				L"\n"
				L"次また追いかけて来ても、この部屋に逃げ込めば\n"
				L"きっと大丈夫だろう。他にも明るい部屋があれば\n"
				L"覚えておいた方が良さそうだ。\n"
				,

				//enMessagePaperKind_02
				L"懐中電灯の部品らしきものを見つけたので、\n"
				L"組み合わせてみたのだが、こいつはいい!\n"
				L"\n"
				L"RB2ボタン長押しでチャージしてから\n"
				L"ボタンを離すことで、強力なフラッシュが\n"
				L"放てるようになった!\n"
				L"\n"
				L"これならあの化け物にも多少は効果があるだろう。\n"
				L"すぐにでもあいつを目潰ししてやりたい所だが、\n"
				L"どうやらこの機能を使うとバッテリーを大きく消耗\n"
				L"してしまうみたいだ。気を付けないとな\n"
				L"\n"
				L"そういえば道の途中に、目のような模様がある\n"
				L"変わった壁があったな。如何にも怪しい壁だったが\n"
				L"もう少し調べてみた方がいいだろうか。\n"
				,

				//enMessagePaperKind_03
				L"また新たな部品を手に入れた。\n"
				L"\n"
				L"驚いたことに、LB2ボタンを押している間\n"
				L"壁越しで化け物の居場所を特定できるらしい。\n"
				L"\n"
				L"薄々気付いてはいたが、どうやらこいつは\n"
				L"ただの懐中電灯じゃなかったらしい。\n"
				L"こいつの力で、あの化け物も\n"
				L"倒せるようになれば最高なんだがな。\n"
				L"\n"
				L"ところで、この部屋を出て右側の壁沿いに\n"
				L"もう一つ部屋があったような気がするのだが\n"
				L"気のせいだろうか...\n"
				,

				//enMessagePaperKind_04
				L"\n"
				L"\n"
				L"ついに最強の力を手に入れたらしい。\n"
				L"\n"
				L"RB2長押しのチャージを、\n"
				L"更に長くチャージし続けることで、\n"
				L"今までよりも強力な光を放てるようになった。\n"
				L"\n"
				L"しかもこれは、どうやらただの光じゃなさそうだ。\n"
				L"これだけの威力があれば、きっとあの化け物にも\n"
				L"とどめをさせるだろう。\n"
				L"\n"
				L"今まで散々苦しめやがって!今に見てろ!\n"
				,

				//enMessagePaperKind_05
				L"\n"
				L"\n"
				L"クソ...\n"
				L"あと少しで脱出できるってのに\n"
				L"もう身体が動きやがらねぇ。\n"
				L"\n"
				L"後ろから奴らが追いかけてくる声が聞こえる。\n"
				L"遂に天命も尽きちまったか...\n"
				L"\n"
				L"もしここまで辿り着けた奴がいるのなら\n"
				L"絶対に振り返らずに、あの光に向かって\n"
				L"走り続けるんだ。\n"
				L"\n"
				L"そうすればきっと...\n"
				,
			};
		}
	}
}