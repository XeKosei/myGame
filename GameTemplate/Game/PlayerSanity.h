#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerSanity : public IGameObject
		{
		public:
			~PlayerSanity();
			bool Start();

			void ExecuteUpdate();

			//Hazyスプライトを設定する
			void SetHazySprite();

			//スプライトの点滅処理
			void HazySpriteBlink();

			//死んだとき
			void DYING();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief プレイヤーのSAN値を指定した値だけ減らす。
			/// @param damageNum 与えるダメージ
			void Damage(float damageNum);

			/// @brief プレイヤーのSAN値を指定した値だけ回復する。
			/// @param recoveryNum 回復量
			void Recovery(int recoveryNum);

			/// @brief プレイヤーが安心できる状態かを設定
			/// @param flag 安心できる:true できない:false
			void SetReliefFlag(bool flag) { m_reliefFlag = flag; }

			/// @brief SAN値を取得
			/// @return 現在のSAN値
			float GetSanityValue() { return m_sanityValue; }
		private:
			//プレイヤー
			Player* m_player = nullptr;
			//プレイヤーのSAN値
			float m_sanityValue = 0.0f;
			//次にダメージを受けることができるようになるまでの間隔
			int m_damageIntervalCount = 0;
			//ダメージを受けた際の画面の周りのスプライト
			SpriteRender* m_hazySprite = nullptr;

			//hazyスプライト関連
			//スプライトの色
			Vector4 m_hazyColor = { 0.0f,0.0f,0.0f,0.0f };
			//スプライトの点滅
			float m_addAlpha = 0.0f;
			bool m_addAlphaFlag = true;

			//HP表示(デバッグ用)
			FontRender* f = nullptr;

			//安心できるかどうか。
			bool m_reliefFlag = false;
		};
	}
}