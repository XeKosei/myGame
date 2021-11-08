#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsItem
	{
		class ItemBase;
		class ItemKey : public IGameObject
		{
		public:
			//鍵の色の種類
			enum EnKeyColor
			{
				enKeyColor_Red,
				enKeyColor_Blue,
				enKeyColor_Green,
				enKeyColor_Yellow,
				enKeyColor_Purple,
				enKeyColor_num
			};

			~ItemKey();
			bool Start();
			void Update();
			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief 鍵の色を設定
			/// @param color 鍵の色
			void SetKeyColor(EnKeyColor color) { m_keyColor = color; }
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_keyModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			EnKeyColor m_keyColor = enKeyColor_Red;
		};
	}
}