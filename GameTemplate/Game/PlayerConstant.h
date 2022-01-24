#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		namespace nsPlayerConstant
		{
			static const Vector3 INI_PLAYER_POSITION = { 1000.0f, 0.0f,0.0f };	//�v���C���[�̏����ʒu
			static const float PLAYER_MODEL_WIDTH = 50.0f;	///:�v���C���[�̃��f���̉���
			static const float PLAYER_MODEL_HEIGHT = 120.0f;	//�v���C���[�̃��f���̍���
			static const Vector3 INI_PLAYER_SCALE = { 1.0f, 1.0f, 1.0f };	//�v���C���[�̃��f���̑傫���̏����l
		}
		//Player�N���X�ŗ��p����萔
		namespace nsPlayerMoveConstant
		{
			static const float PLAYER_WALK_SPEED = 80.0f;	//�v���C���[�̕�������
			static const float PLAYER_DASH_SPEED = PLAYER_WALK_SPEED * 2.0f;//�v���C���[�̑��鑬��
			static const float PLAYER_CROUCHDOWN_WALK_SPEED = PLAYER_WALK_SPEED / 2.0f;//�v���C���[�̋��ݕ����̑���
			static const float PLAYER_MOVE_FRICTION = 0.2f;	//�v���C���[�������Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;		//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��

			static const float FOOTSTEP_SE_INTERVAL = 200;	//�����̊Ԋu
		}

		namespace nsPlayerCameraConstant
		{
			static const float CAMERA_MOVE_SPEED = 3.0f;		//�J��������������
			static const float INI_PLAYER_EYE_HEIGHT = 250.0f;		//�v���C���[�̖ڂ̍���
			static const float TO_CAMERA_TARGET_DIS = 100.0f;	//�J�����̃^�[�Q�b�g�ւ̋���

			static const float ADD_EYEHEIGHT_SPEED_IDLE = 0.02f;	//�J�������ċz�ŏ㉺���鑬��
			static const float MAX_ADD_EYEHEIGHT = 2.0f;	//�J�������ċz�ŏ㉺����ő���Z�l
			static const float MIN_ADD_EYEHEIGHT = -2.0f;	//�J�������ċz�ŏ㉺����ŏ����Z�l
		}

		namespace nsPlayerActionConstant
		{
			static const float CROUCHDOWN_PLAYER_EYE_HEIGHT = 100.0f;		//�v���C���[������ł��鎞�̖ڂ̍���
			static const Vector3 CROUCHDOWN_PLAYER_SCALE = { 1.0f, 0.5f, 1.0f };	//�v���C���[�̃��f���̑傫���̏����l
		}

		namespace nsPlayerSanityConstant
		{
			static const float MAX_PLAYER_SANITY = 100.0f;	//�v���C���[��SAN�l�̍ő�l
			static const int DAMAGE_INTERVAL = 200;	//���Ƀ_���[�W���󂯂���悤�ɂȂ�܂ł̊Ԋu
			
			static const float BIG_DAMAGE_LINE = MAX_PLAYER_SANITY / 3;	//��_���[�W���󂯂Ă���Ɣ��f����郉�C��

			static const float DARKNESS_SANITY_DAMAGE_SPEED = 0.05f;	//�Â�����SAN�l�����킶��ƌ����Ă����X�s�[�h
		
			static const float BLOODSPRITE_DEC_SPEED = 0.02f;	//�_���[�W���̃X�v���C�g�̏����鑬��
			static const float MAX_BLOODSPRITE_COLOR = 2.0f;	//�_���[�W���̃X�v���C�g�̍ő�J���[
		}

		namespace nsPlayerBittenConstant
		{
			static const int INI_CAN_MOVE_INTERVAL = 30;	//������悤�ɂȂ�܂ł̃C���^�[�o��
			static const int RESIST_TO_BITE_NUM = 100;	//���݂��ɒ�R���鐔�l	
			static const float CAMERA_TURN_SPEED = 0.2f;	//�J�������U���������
		}

		namespace nsPlayerPouchConstant
		{
			static const int TRANQUILIZER_RECOVERY_NUM = 50.0f;	//���_����܂��g�������̉񕜗�
		}

		namespace nsPlayerTargetConstant
		{
			static const float CATCH_EYES_DIS = 400.0f;	//�I�u�W�F�N�g���v���C���[�̖ڂ���������
			static const float CATCH_EYES_DOT = 0.95f;	//�I�u�W�F�N�g���v���C���[�̖ڂ���������
			static const Vector2 ITEMNAME_FONT_POS = {-50.0f,-200.0f};	//�A�C�e�����̕\���ʒu
			static const float ITEMNAME_FONT_SCALE = 0.65f;	//�A�C�e�����̃t�H���g�̑傫��
			
			//�^�[�Q�b�g�̖��O
			static const std::wstring TARGET_NAME[PlayerTarget::enTarget_num] = { 
				L"", L"A �h�A", L"A ��", L"A �����d���̕��i", 
				L"A ���_�����",L"A �d�r", L"A ��"};
			
			//�R�}���h�\��
			static const std::wstring COMMAND_TEXT[PlayerTarget::enCommand_num] = {L"", L"A:�E��",L"A:�J����",L"A:�߂�", L"A:�ǂ�"};
			
			static const Vector2 COMMAND_FONT_POS = { 400.0f, -250.0f };	//�R�}���h�t�H���g�̈ʒu
		}

		namespace nsPlayerReadConstant
		{
			static const float ADD_BLACKSPRITE_COLOR_SPEED = 0.05f;	//��ʂ��Â����鑬��
			static const float MAX_BLACKSPRITE_COLOR = 0.5f;	//���X�v���C�g�̍ő�J���[
		}

		namespace nsPlayerUIConstant
		{
			/////////////////////////////HazySprite�֘A
			static const Vector4 INI_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 0.0f };	//Hazy�X�v���C�g�̏����J���[
			static const Vector4 DAMAGED_HAZYSPRITE_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };	//�_���[�W���󂯂��ۂ�Hazy�X�v���C�g�̃J���[
			static const float HAZYSPRITE_MUL_COLOR_PINCH = 20.0f;	//�s���`����Hazy�X�v���C�g�̃J���[�Ɋ|����l

			static const float MUL_HAZYSPRITE_COLOR_VALUE = 1.5f;	//HazySprite�̃J���[�ɂ�����l

			static const float ADD_ALPHA_SPEED = 0.001f;	//�X�v���C�g���_�ł��鑬��
			static const float MAX_ADD_ALPHA = 0.02f;		//�_�ł̍ő���Z�l
			static const float MIN_ADD_ALPHA = -0.02f;		//�_�ł̍ŏ����Z�l

			static const float DYING_ADD_ALPHA_SPEED = 0.5f;	//���񂾂Ƃ��̃A���t�@�l���Z�̑���
			static const float DYING_MAX_ADD_ALPHA = 100.0f;	//���񂾂Ƃ��̃A���t�@�l�̍ő���Z�l
				
			///////////////////////////////�|�[�`�A�C�e���֘A
			static const Vector2 INI_ITEMFONT_POS = { -550.0f, -285.0f };	//�|�[�`�A�C�e���̃t�H���g�̈ʒu
			static const float INI_ITEMFONT_SCALE = 0.55f;	//�|�[�`�A�C�e���̃t�H���g�̃X�P�[��
			static const Vector2 INI_ITEMNUMFONT_POS = { -425.0f, -285.0f };	//�|�[�`�A�C�e���̐��̕\���ʒu
			static const float INI_ITEMNUMFONT_SCALE = 0.6f;	//�A�C�e�����̃t�H���g�̃X�P�[��

			//�A�C�e����
			static const std::wstring ITEM_NAME[PlayerPouch::enItem_num] = {
				L"   �d�r   ", L"���_�����" , L" �ԐF�̌�", L" �F�̌�", L" �ΐF�̌�",
				L" ���F�̌�", L" ���F�̌�", L" �Ō�̌�" };

			//�A�C�e���A�C�R���̃X�v���C�g�̃t�@�C���p�X
			static const char* ITEMSPRITE_FILEPATH[PlayerPouch::enItem_num] = {
				"Assets/Image/BatteryIcon.DDS",
				"Assets/Image/TranquilizerIcon.DDS",
				"Assets/Image/RedKeyIcon.DDS",
				"Assets/Image/BlueKeyIcon.DDS",
				"Assets/Image/GreenKeyIcon.DDS",
				"Assets/Image/YellowKeyIcon.DDS",
				"Assets/Image/PurpleKeyIcon.DDS",
				"Assets/Image/WhiteKeyIcon.DDS"
			};
			static const Vector3 INI_ITEMSPRITE_POS = {-490.0f, -260.0f, 0.0f};	//�A�C�e���A�C�R���̈ʒu
			static const Vector3 INI_ITEMSPRITE_SCALE = {0.2f,0.2f,0.2f};	//�A�C�e���A�C�R���̑傫��

			///////////////////////////////�o�b�e���[�֘A
			static const Vector3 INI_BATTERYSPRITE_POS = { 540.0f, 285.0f , 0.0f };	//�o�b�e���[�\���̈ʒu
			static const Vector3 INI_BATTERYSPRITE_SCALE = { 0.3f,0.3f,0.3f };	//�o�b�e���[�\���̏����X�P�[��
			
			//�o�b�e���[�\����ς��郉�C��
			static const float BATTERYSPRITE_CHANGE_LINE[PlayerUI::enBatteryDispTypes_num] = 
			{0.0f,0.0f,25.0f,50.0f,75.0f};

			//�o�b�e���[�X�v���C�g�̃t�@�C���p�X
			static const char* BATTERYSPRITE_FILEPATH[PlayerUI::enBatteryDispTypes_num] = {
				"Assets/Image/Battery0.DDS",
				"Assets/Image/Battery1.DDS",
				"Assets/Image/Battery2.DDS",
				"Assets/Image/Battery3.DDS",
				"Assets/Image/Battery4.DDS"
			};

			static const float BATTERY_UI_DELETE_SPEED = 0.05f;	//�o�b�e���[UI����������
		}
	}
}
