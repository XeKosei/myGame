#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerPouch
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

			enum EnUseItemSounds
			{
				enUseItemSounds_Battery,
				enUseItemSounds_Tranquilizer,
				enUseItemSounds_Key,
				enUseItemSounds_num,
			};

			~PlayerPouch();
			void Init(Player* pl);
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

			//�A�C�e���g�p����SE 
			void UseItemSE(EnUseItemSounds soundKind);
			//
			//void CannotUse();

			/// @brief �w�肵���A�C�e������|�[�`�ɒǉ�����
			/// @param item �ǉ�����A�C�e��
			void AddItem(EnPlayerItems item); 

		private:
			//�v���C���[
			Player* m_player = nullptr;

			int m_choseItem = enItem_Battery;
			int m_haveItemNum[enItem_num] = { 5, 1, 1, 1, 1, 1, 1, 1};

			SoundSource* m_useItemSS = nullptr;
		};
	}
}