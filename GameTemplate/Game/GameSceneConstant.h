#pragma once
namespace nsHikageri
{
	namespace nsGameScene
	{


		namespace nsGameOverConstant
		{
			static const int INI_GAMEOVER_EXECUTE_COUNT = 650;	//�Q�[���I�[�o�[��ʎ��s���̃J�E���g�����l
			static const int DISPLAY_SPRITE_TIMING = 500;	//�X�v���C�g����ʂɕ\������^�C�~���O�B
			static const int DELETE_SPRITE_TIMING = 100;	//�X�v���C�g�̕\���������^�C�~���O
			
			static const float ADD_ALPHA_SPEED = 0.01f;	//�X�v���C�g�̃J���[�ɃA���t�@�l�����Z���鑬��
			static const float MAX_GAMEOVER_SPRITE_ALPHA = 1.0f;	//�Q�[���I�[�o�[�\���̃J���[�̍ő�A���t�@�l
		
		}

		namespace nsGameClearConstant
		{
			static const int INI_GAMECLEAR_EXECUTE_COUNT = 1300;	//�Q�[���N���A��ʎ��s���̃J�E���g�����l
			static const int DISPLAY_TITLENAME_TIMING = 1050;	//�^�C�g��������ʂɕ\������^�C�~���O�B
			static const int DELETE_TITLENAME_TIMING = 700;	//�^�C�g�����̕\���������^�C�~���O
			static const int DISPLAY_CLEARFONT_TIMING = 600;	//�N���A�t�H���g��\������^�C�~���O
			static const int DELETE_CLEARFONT_TIMING = 300;	//�N���A�t�H���g�������^�C�~���O
			static const int DELETE_GAMESCENE_TIMING = 1200;	//�Q�[���V�[���������^�C�~���O

			static const float WHITESPRITE_ADD_SPEED = 0.01f;	//���X�v���C�g��\�����鑬��
			static const float TITLENAME_DELETE_SPEED = 0.01f;	//�^�C�g�����̕\������������
			static const float CLEARFONT_ADD_SPEED = 0.02f;	//�N���A�t�H���g��\�����鑬��
		
			static const Vector2 CLEARFONT_POS = { -250.0f, 50.0f };	//�N���A�t�H���g�̕\���ʒu
		}
	}
}