#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerPouch;
		class PlayerUI
		{
		public:
			//�o�b�e���[�̕\���̎��
			enum EnBatteryDispTypes
			{
				enBatteryDispTypes_runOut,	//�o�b�e���[���Ȃ���
				enBatteryDispTypes_moreThan00,	//�c�ʂ�0�ȏ�
				enBatteryDispTypes_moreThan25,	//25�ȏ�
				enBatteryDispTypes_moreThan50,	//50�ȏ�
				enBatteryDispTypes_moreThan75,	//75�ȏ�
				enBatteryDispTypes_num
			};


			~PlayerUI();
			void Init(Player* pl);
			void ExecuteUpdate();

			//Hazy�X�v���C�g��ݒ肷��
			void SetHazySprite();

			//�X�v���C�g�̓_�ŏ���
			void BlinkHazySprite();

			//���񂾂Ƃ�
			void DyingHazySprite();

			/// @brief �|�[�`�A�C�e���\����ݒ�
			/// @param item �A�C�e���̎��
			/// @param itemNum �A�C�e���̔ԍ�
			void SetItemFont(int itemKind, int itemNum);

			/// @brief �o�b�e���[�\����ݒ�
			/// @param batteryLevel �o�b�e���[�c��
			void SetBatterySprite(float batteryLevel);
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

			//�|�[�`�A�C�e���̉�ʕ\��
			FontRender* m_itemFont = nullptr;
			FontRender* m_itemNumFont = nullptr;
			SpriteRender* m_itemSprite[PlayerPouch::enItem_num] = { 
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr, nullptr, nullptr};
			int m_itemSpriteNum = 0;

			//�o�b�e���[�\��
			SpriteRender* m_batterySprite[enBatteryDispTypes_num] = { nullptr, nullptr, nullptr, nullptr, nullptr };
			EnBatteryDispTypes m_batteryDispType = enBatteryDispTypes_moreThan00;
		};
	}
}

