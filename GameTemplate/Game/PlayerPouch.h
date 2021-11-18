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
			void AddItem(EnPlayerItems item) { m_haveItemNum[item]++; 
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			}

			bool Start();
			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//プレイヤー
			Player* m_player = nullptr;

			//アイテムの画面表示
			FontRender* m_itemFont = nullptr;
			FontRender* m_itemNumFont = nullptr;

			//アイテム使用時のテキスト表示
			/*FontRender* m_itemUsedFont = nullptr;
			int m_itemUsedFontCount = 0;
			Vector4 m_itemUsedFontColor = {0.0f,0.0f,0.0f,0.0f};*/

			int m_choseItem = enItem_Battery;
			int m_haveItemNum[enItem_num] = { 10, 10, 0, 0, 0, 0, 0, 0};
		};
	}
}