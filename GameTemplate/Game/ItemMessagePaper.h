#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsItem
	{
		class ItemMessagePaper : public IGameObject
		{
		public:
			//この紙に書かれている内容
			enum EnMessagePaperKinds
			{
				enMessagePaperKind_00,
				enMessagePaperKind_01,
				enMessagePaperKind_02,
				enMessagePaperKind_03,
				enMessagePaperKind_04,
				enMessagePaperKind_05,
				enMessagePaperKind_06,
				enMessagePaperKind_07,
				enMessagePaperKind_num
			};

			~ItemMessagePaper();
			bool Start();
			void Update();
			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief 紙に書かれている内容を設定
			/// @param messagePaperText 設定する内容
			void SetMessagePaperText(EnMessagePaperKinds kind) { m_kind = kind; };
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_paperModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			EnMessagePaperKinds m_kind = enMessagePaperKind_00;
		};
	}
}