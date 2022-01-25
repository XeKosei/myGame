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
				L"\n"
				L"\n"
				L"�ڂ��o�܂��ƁA�����͓�̕���\n"
				L"\n"
				L"�����Ă���̂́A���m��ʉ����d���̂�\n"
				L"\n"
				L"�܂��͕ӂ�𒲂ׂĂ݂悤...\n"
				L"\n"
				L"\n"
				L"\n"
				L"              - ���� -              \n"
				L"\n"
				L"     R1�{�^�� : �����d���̃X�C�b�`\n"
				L"\n"
				L"     L1�{�^�� :      ����\n"
				L"\n"
				L"     X �{�^�� : �A�C�e���̎g�p\n"
				L"\n"
				L"                                              Loading...\n"
			};
		}
	}
}