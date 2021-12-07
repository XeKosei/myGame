#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerPouch
		{
		public:
			//アイテムの種類
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

			//アイテムを選択する
			void SelectItem();

			//アイテムを使う
			void UseItem();

			//電池を使用したときの処理
			void UseBattery();

			//精神安定剤を使用したとき
			void UseTranquilizar();

			//鍵を使用したとき
			void UseKey();

			//アイテム使用時のSE 
			void UseItemSE(EnUseItemSounds soundKind);
			//
			//void CannotUse();

			/// @brief 指定したアイテムを一つポーチに追加する
			/// @param item 追加するアイテム
			void AddItem(EnPlayerItems item); 

		private:
			//プレイヤー
			Player* m_player = nullptr;

			int m_choseItem = enItem_Battery;
			int m_haveItemNum[enItem_num] = { 5, 1, 1, 1, 1, 1, 1, 1};

			SoundSource* m_useItemSS = nullptr;
		};
	}
}