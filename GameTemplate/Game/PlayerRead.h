#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerRead
		{
		public:
			~PlayerRead();
			void Init(Player* pl);
			void ExecuteUpdate();

			/// @brief テキストを設定
			/// @param message テキスト
			void SetMessage(std::wstring message) { m_message = message; }

		private:
			//プレイヤー
			Player* m_player = nullptr;

			FontRender* m_messageFont = nullptr;

			std::wstring m_message = L"";

			SpriteRender* m_blackSprite = nullptr;
			Vector4 m_blackSpriteColor = {0.0f,0.0f,0.0f,0.0f};
			//画面を暗くするフラグ
			bool m_blackOutFlag = false;
		};

	}
}