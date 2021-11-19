#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }

	namespace nsGimmick
	{
		class ChandelierManager : public IGameObject
		{
		public:
			bool Start();
			void Update();
			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }
			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };
		private:
			//�v���C���[�ƃG�l�~�[
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			//�X�|�b�g���C�g
			SpotLight* m_spotLig[2] = { nullptr, nullptr };

			//�V�����f���A
			nsGimmick::Chandelier* m_chandelier[10] = {
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr,nullptr };
			//�V�����f���A�̈ʒu
			Vector3 m_chandelierPos[10] = {
				{ 1000.0f,800.0f,0.0f } ,
				{ -1000.0f, 800.0f, 1000.0f},
				{-1400.0f, 800.0f, -3600.0f},
				{-1000.0f, 800.0f, 3400.0f},
				{0.0f, 800.0f, -2000.0f},
				{-4600.0f, 800.0f, 2800.0f},
				{-9000.0f, 800.0f,6000.0f},
				{-4600.0f, 800.0f, 4400.0f},
				{600.0f, 800.0f, 4400.0f,},
				{600.0f, 800.0f, 6000.0f,}
			};
		};
	}
}