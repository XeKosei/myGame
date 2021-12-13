#pragma once
namespace nsHikageri
{
	namespace nsTitleScene
	{
		namespace nsTitleSceneConstant
		{
			static const Vector2 TITLEFONT_POS = { -150.0f, -200.0f };	//�^�C�g���t�H���g�̈ʒu
			static const float TITLEFONT_SCALE = 0.7f;	//�^�C�g���t�H���g�̑傫��
			static const int SECOND_MOVE_INTERVAL = 20;	//SecondMove�Ɉڍs����܂ł̊Ԋu

			static const float TITLESPRITE_COLOR_ADD_SPEED = 0.03f;	//�^�C�g����ʂ�\�����鑬��
			static const float TITLEFONT_COLOR_ADD_SPEED = 0.03f;	//�^�C�g����ʂ̕�����\�����鑬��

			static const float BLINKING_COLOR_ADD_SPEED = 0.008f;	//�_�ł̑���
			static const float BLINKING_MIN_COLOR = 0.6f;	//�_�ł̍ő�J���[

			static const float TITLESPRITE_DELETE_SPEED = 0.02f;	//�^�C�g����ʂ����킶���������
			static const float TITLESPRITE_DELETE_MAX_COLOR = 2.0f;	//�^�C�g����ʂ������Ƃ��̍ŏ��̐F

			static const Vector2 SYNOPSISFONT_POS = {-320.0f, 260.0f};	//���炷���̕\���ʒu
			static const float SYNOPSISFONT_SCALE = 0.7f;	//���炷���t�H���g�̑傫��
			static const float SYNOPSISFONT_COLOR_ADD_SPEED = 0.02f;	//���炷���̕\���̑���

			static const float BLACKSPRITE_DELETE_SPEED = 0.05f;	//���w�i����������

			static const std::wstring SYNOPSIS =
			{
				L"�ڂ��o�܂��ƁA�����͌��m��ʕ����������B\n"
				L"\n"
				L"�����͂ǂ����낤�B���̊Ԃɂ���ȏꏊ��?\n"
				L"\n"
				L"����Ȃǂ͂Ȃ��������̑̂��m�F����ƁA\n"
				L"���̊Ԃɂ��E��ɒm��Ȃ������d����\n"
				L"�����Ă��邱�ƂɋC���t�����B\n"
				L"\n"
				L"�ӂ�͔��Â��āA�ƂĂ��s���ɂȂ�B\n"
				L"\n"
				L"�Ƃ肠�����A�܂��͂��̉����d�����g����\n"
				L"�ӂ�𒲂ׂĂ݂āA�󋵂�c�����悤...\n"
				L"\n"
				L"              - ���� -              \n"
				L"\n"
				L"      R�{�^��:�����d���̃X�C�b�`\n"
				L"      L�{�^��:����\n"
				L"      X�{�^��:�A�C�e�����g��\n"
				L"                                              Loading...\n"
			};
		}
	}
}