#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerPouch : public IGameObject
		{
		public:
			//�A�C�e���̎��
			enum EnPlayerItems
			{
				enItem_Battery,
				enItem_Tranquilizer,
				enItem_RedKey,
				enItem_BlueKey,
				enItem_GreenKey,
				enItem_YellowKey,
				enItem_PurpleKey,
				enItem_LastKey,
				enItem_num
			};

			~PlayerPouch();
			void ExecuteUpdate();

			//�A�C�e����I������
			void SelectItem();

			//�A�C�e�����g��
			void UseItem();

			//�d�r���g�p�����Ƃ��̏���
			void UseBattery();

			//���_����܂��g�p�����Ƃ�
			void UseTranquilizar();

			//�����g�p�����Ƃ�
			void UseKey();

			//
			//void CannotUse();

			/// @brief �w�肵���A�C�e������|�[�`�ɒǉ�����
			/// @param item �ǉ�����A�C�e��
			void AddItem(EnPlayerItems item); 

			bool Start();
			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//�v���C���[
			Player* m_player = nullptr;

			int m_choseItem = enItem_Battery;
			int m_haveItemNum[enItem_num] = { 5, 1, 1, 1, 1, 1, 1, 1};
		};
	}
}