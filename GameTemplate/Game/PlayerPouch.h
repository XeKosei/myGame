#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerPouch : public IGameObject
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

			~PlayerPouch();
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

			//
			//void CannotUse();

			/// @brief 指定したアイテムを一つポーチに追加する
			/// @param item 追加するアイテム
			void AddItem(EnPlayerItems item); 

			bool Start();
			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//プレイヤー
			Player* m_player = nullptr;

			int m_choseItem = enItem_Battery;
			int m_haveItemNum[enItem_num] = { 5, 1, 1, 1, 1, 1, 1, 1};
		};
	}
}