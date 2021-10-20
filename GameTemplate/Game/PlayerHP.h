#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerHP : public IGameObject
		{
		public:
			bool Start();

			void ExecuteUpdate();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief �v���C���[�̃_���[�W���w�肵���l�������炷�B
			/// @param damageNum �^����_���[�W
			void Damage(int damageNum);
			
		private:
			//�v���C���[
			Player* m_player = nullptr;
			//�v���C���[�̗̑�
			int m_HP = 0.0f;
			//���Ƀ_���[�W���󂯂邱�Ƃ��ł���悤�ɂȂ�܂ł̊Ԋu
			int m_damageIntervalCount = 0;
		};
	}
}