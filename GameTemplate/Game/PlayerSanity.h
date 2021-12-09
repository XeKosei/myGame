#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerSanity
		{
		public:
			~PlayerSanity();
			void Init(Player* pl);
			void ExecuteUpdate();	

			//心音
			void Heartbeat();

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
			//安心できるかどうか。
			bool m_reliefFlag = false;

			//HP表示(デバッグ用)
			FontRender* f = nullptr;

			//心音関連
			int m_heartbeatInterval = 0;
			int m_heartbeatIntervalCount = 0;
		};
	}
}