#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }

	namespace nsGimmick
	{
		class Chandelier : public IGameObject
		{
		public:
			bool Start();

			void Update();

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			SkinModelRender* m_chandelierModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			//�|�C���g���C�g
			PointLight* m_pointLig = nullptr;

			//�v���C���[�ƃG�l�~�[
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;
		};
	}
}