#pragma once
//�G�l�~�[�ɂ��݂��ꂽ�Ƃ��̏���
namespace nsHikageri
{
	namespace nsEnemy { class Enemy; };
	namespace nsPlayer
	{
		class Player;
		class PlayerBitten
		{
		public:
			~PlayerBitten();
			void Init(Player* pl);

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

			//���݂����Ԃ�J��
			void SetBittenState(EnBittenStates state) { m_bittenStates = state; };

			//�͂�ł����G�l�~�[��ݒ�
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; }
		private:
			Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;
			//���݂��ꒆ�̏����̑J��
			EnBittenStates m_bittenStates = enBittenState_PreBitten;

			int m_canMoveInterval = 0;
		};
	}
}
