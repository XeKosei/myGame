#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsItem
	{
		class ItemMessagePaper : public IGameObject
		{
		public:
			//���̎��ɏ�����Ă�����e
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

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief ���ɏ�����Ă�����e��ݒ�
			/// @param messagePaperText �ݒ肷����e
			void SetMessagePaperText(EnMessagePaperKinds kind) { m_kind = kind; };
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_paperModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			EnMessagePaperKinds m_kind = enMessagePaperKind_00;
		};
	}
}