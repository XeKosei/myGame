#pragma once
//�G�l�~�[�ɂ��݂��ꂽ�Ƃ��̏���
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

			//���݂����Ԃ�J��
			void SetBittenState(EnBittenStates state) { m_bittenStates = state; };

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

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
