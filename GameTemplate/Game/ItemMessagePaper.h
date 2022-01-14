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

			//����G�t�F�N�g
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
		};

		namespace nsItemMessagePaperConstant
		{
			static const std::wstring MESSAGEPAPAER_TEXT[ItemMessagePaper::enMessagePaperKind_num] =
			{
				//enMessagePaperKind_00
				L"�����N�����ǂ�ł���邱�Ƃ��肤�B\n"
				L"\n"
				L"���̖��O�̓_�j�G��\n"
				L"�C���t���Ƃ���ȏꏊ�œ|��Ă����B\n"
				L"\n"
				L"�����͌��n������^���ÂŁA�������E����\n"
				L"�����d���̖����肪�����ƁA���̂�\n"
				L"���񂾂�̗͂������Ȃ��Ă���C������B\n"
				L"\n"
				L"����ɂ���������ςș�����������Ă���B\n"
				L"������������N������̂�������Ȃ���...\n"
				L"\n"
				L"�d���˂�����A���͏���������Ă��悤�Ǝv���B\n"
				L"\n"
				L"�����N������̂Ȃ�A�ꏏ�ɏo����T���Ă���!\n"
				,

				//enMessagePaperKind_01
				L"��̂Ȃ�Ȃ񂾂��̉�������!\n"
				L"�������������r�[�A�Y���т��グ��\n"
				L"�ǂ������ė��₪����!\n"
				L"\n"
				L"���ꂿ�܂����Ǝv�������A�ǂ����Q�Ă�\n"
				L"�������񂾂̂����̕����Ő����������炵���B\n"
				L"\n"
				L"�ǂ����z�͋����������Ȃ悤���B\n"
				L"�Ƃ͌����Ă����̉����d���̌����炢�Ȃ�\n"
				L"���C�Ȃ悤����...\n"
				L"\n"
				L"���܂��ǂ������ė��Ă��A���̕����ɓ������߂�\n"
				L"�����Ƒ��v���낤�B���ɂ����邢�����������\n"
				L"�o���Ă����������ǂ��������B\n"
				,

				//enMessagePaperKind_02
				L"�@��̕��i�炵�����̂��������̂ŁA\n"
				L"�����d���ɍ��̂����Ă݂��̂����A�����͂���!\n"
				L"\n"
				L"RB2�{�^���������Ń`���[�W���Ă���\n"
				L"�{�^���𗣂����ƂŁA���͂ȃt���b�V����\n"
				L"���Ă�悤�ɂȂ���!\n"
				L"\n"
				L"����Ȃ炠�̉������ɂ������͌��ʂ����邾�낤�B\n"
				L"�����ɂł�������ڒׂ����Ă�肽���������A\n"
				L"�ǂ���炱�̋@�\���g���ƃo�b�e���[��傫������\n"
				L"���Ă��܂��݂������B�C��t���Ȃ��ƂȁB\n"
				L"\n"
				L"���������Γ��̓r���ɁA�ڂ̂悤�Ȗ͗l������\n"
				L"�ς�����ǂ��������ȁB�@���ɂ��������ǂ�������\n"
				L"�����������ׂĂ݂������������낤���B\n"
				,

				//enMessagePaperKind_03
				L"�܂��V���ȕ��i����ɓ��ꂽ�B\n"
				L"\n"
				L"���������ƂɁALB2�������Ă����\n"
				L"�ǉz���ŉ������̋��ꏊ�����ł���炵���B\n"
				L"\n"
				L"���X�C�t���Ă͂������A�ǂ���炱����\n"
				L"�����̉����d������Ȃ������炵���B\n"
				L"�����̗͂ŁA���̉�������\n"
				L"�|����悤�ɂȂ�΍ō��Ȃ񂾂��ȁB\n"
				L"\n"
				L"�Ƃ���ŁA���̕������o�ĉE���̕ǉ�����\n"
				L"������������������悤�ȋC������̂���\n"
				L"�C�̂������낤��...\n"
				,

				//enMessagePaperKind_04
				L"���ɍŋ��̗͂���ɓ��ꂽ�炵���B\n"
				L"\n"
				L"RB2�������̃`���[�W���A\n"
				L"�X�ɒ����`���[�W�������邱�ƂŁA\n"
				L"���܂ł������͂Ȍ�����Ă�悤�ɂȂ����B\n"
				L"\n"
				L"����������́A�ǂ���炽���̌�����Ȃ��������B\n"
				L"���ꂾ���̈З͂�����΁A�����Ƃ��̉������ɂ�\n"
				L"�Ƃǂ߂������邾�낤�B\n"
				L"\n"
				L"���܂ŎU�X�ꂵ�߂₪����!���Ɍ��Ă�!\n"
				,

				//enMessagePaperKind_05
				L"Test\n"
				,
			};
		}
	}
}