#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerUI : public IGameObject
		{
		public:
			~PlayerUI();
			bool Start();
			void ExecuteUpdate();

			//Hazy�X�v���C�g��ݒ肷��
			void SetHazySprite();

			//�X�v���C�g�̓_�ŏ���
			void BlinkHazySprite();

			//���񂾂Ƃ�
			void DyingHazySprite();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//�v���C���[
			Player* m_player = nullptr;

			//�_���[�W���󂯂��ۂ̉�ʂ̎���̃X�v���C�g
			SpriteRender* m_hazySprite = nullptr;
			//hazy�X�v���C�g�֘A
			//�X�v���C�g�̐F
			Vector4 m_hazyColor = { 0.0f,0.0f,0.0f,0.0f };
			//�X�v���C�g�̓_��
			float m_addAlpha = 0.0f;
			bool m_addAlphaFlag = true;
		};
	}
}

