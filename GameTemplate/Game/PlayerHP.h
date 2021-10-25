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

			void SetBloodSprite();

			void BloodSpriteBlink();

			void GameOver();//��

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
			int m_HP = 0;
			//���Ƀ_���[�W���󂯂邱�Ƃ��ł���悤�ɂȂ�܂ł̊Ԋu
			int m_damageIntervalCount = 0;
			//�_���[�W���󂯂��ۂ̉�ʂ̎���̌��̕\��
			SpriteRender* m_bloodSprite = nullptr;

			//��ʒ[�̌��̃X�v���C�g�֘A
			//���̐F
			Vector4 m_bloodColor = {0.0f,0.0f,0.0f,0.0f};
			//���̓_��
			float m_addAlpha = 0.0f;
			bool m_addRedFlag = true;

			//HP�\��(�f�o�b�O�p)
			FontRender* f = nullptr;


			FontRender* m_gameOverFont = nullptr;
			Vector4 m_gameOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
			Vector4 m_gameOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };
			int m_gameOverMoveCount = 250.0f;
		};
	}
}