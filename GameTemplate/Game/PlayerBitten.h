#pragma once
//エネミーにかみつかれたときの処理
namespace nsHikageri
{
	namespace nsEnemy { class Enemy; };
	namespace nsPlayer
	{
		class Player;
		class PlayerBitten : public IGameObject
		{
		public:
			~PlayerBitten();
			bool Start();

			enum EnBittenStates
			{
				enBittenState_PreBitten,
				enBittenState_Bitten,
				enBittenState_EndBitten,
				enBittenStateNum
			};

			void ExecuteUpdate();

			void PreBitten();
			void Bitten();
			void EndBitten();

			//噛みつかれ状態を遷移
			void SetBittenState(EnBittenStates state) { m_bittenStates = state; };

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			//掴んできたエネミーを設定
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; }
		private:
			Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;
			//噛みつかれ中の処理の遷移
			EnBittenStates m_bittenStates = enBittenState_PreBitten;

			int m_canMoveInterval = 0;
		};
	}
}
