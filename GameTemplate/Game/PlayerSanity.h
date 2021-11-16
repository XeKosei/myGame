#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerSanity : public IGameObject
		{
		public:
			bool Start();

			void ExecuteUpdate();

			//Hazy�X�v���C�g��ݒ肷��
			void SetHazySprite();

			//�X�v���C�g�̓_�ŏ���
			void HazySpriteBlink();

			void GameOver();//��

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief �v���C���[��SAN�l���w�肵���l�������炷�B
			/// @param damageNum �^����_���[�W
			void Damage(float damageNum);

			/// @brief �v���C���[��SAN�l���w�肵���l�����񕜂���B
			/// @param recoveryNum �񕜗�
			void Recovery(int recoveryNum);

			/// @brief �v���C���[�����S�ł����Ԃ���ݒ�
			/// @param flag ���S�ł���:true �ł��Ȃ�:false
			void SetReliefFlag(bool flag) { m_reliefFlag = flag; }

		private:
			//�v���C���[
			Player* m_player = nullptr;
			//�v���C���[��SAN�l
			float m_sanityValue = 0.0f;
			//���Ƀ_���[�W���󂯂邱�Ƃ��ł���悤�ɂȂ�܂ł̊Ԋu
			int m_damageIntervalCount = 0;
			//�_���[�W���󂯂��ۂ̉�ʂ̎���̃X�v���C�g
			SpriteRender* m_hazySprite = nullptr;

			//hazy�X�v���C�g�֘A
			//�X�v���C�g�̐F
			Vector4 m_hazyColor = { 0.0f,0.0f,0.0f,0.0f };
			//�X�v���C�g�̓_��
			float m_addAlpha = 0.0f;
			bool m_addAlphaFlag = true;

			//HP�\��(�f�o�b�O�p)
			FontRender* f = nullptr;

			//���S�ł��邩�ǂ����B
			bool m_reliefFlag = false;

			FontRender* m_gameOverFont = nullptr;
			Vector4 m_gameOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
			Vector4 m_gameOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };
			int m_gameOverMoveCount = 250.0f;
		};
	}
}