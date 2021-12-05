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
			//バッテリーの表示の種類
			enum EnBatteryDispTypes
			{
				enBatteryDispTypes_runOut,	//バッテリーがない時
				enBatteryDispTypes_moreThan00,	//残量が0以上
				enBatteryDispTypes_moreThan25,	//25以上
				enBatteryDispTypes_moreThan50,	//50以上
				enBatteryDispTypes_moreThan75,	//75以上
				enBatteryDispTypes_num
			};


			~PlayerUI();
			void Init(Player* pl);
			void ExecuteUpdate();

			//Hazyスプライトを設定する
			void SetHazySprite();

			//スプライトの点滅処理
			void BlinkHazySprite();

			//死んだとき
			void DyingHazySprite();

			/// @brief ポーチアイテム表示を設定
			/// @param item アイテムの種類
			/// @param itemNum アイテムの番号
			void SetItemFont(int itemKind, int itemNum);

			/// @brief バッテリー表示を設定
			/// @param batteryLevel バッテリー残量
			void SetBatterySprite(float batteryLevel);
		private:
			//プレイヤー
			Player* m_player = nullptr;

			//ダメージを受けた際の画面の周りのスプライト
			SpriteRender* m_hazySprite = nullptr;
			//hazyスプライト関連
			//スプライトの色
			Vector4 m_hazyColor = { 0.0f,0.0f,0.0f,0.0f };
			//スプライトの点滅
			float m_addAlpha = 0.0f;
			bool m_addAlphaFlag = true;

			//ポーチアイテムの画面表示
			FontRender* m_itemFont = nullptr;
			FontRender* m_itemNumFont = nullptr;
			SpriteRender* m_itemSprite[PlayerPouch::enItem_num] = { 
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr, nullptr, nullptr};
			int m_itemSpriteNum = 0;

			//バッテリー表示
			SpriteRender* m_batterySprite[enBatteryDispTypes_num] = { nullptr, nullptr, nullptr, nullptr, nullptr };
			EnBatteryDispTypes m_batteryDispType = enBatteryDispTypes_moreThan00;
		};
	}
}

