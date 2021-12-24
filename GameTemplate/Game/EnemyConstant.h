#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		namespace nsEnemyConstant
		{
			static const float ENEMY_MODEL_WIDTH = 10.0f;	//�v���C���[�̃��f���̉���
			static const float ENEMY_MODEL_HEIGHT = 120.0f;	//�v���C���[�̃��f���̍���
			static const Vector3 INI_ENEMY_SCALE = {1.2f, 1.2f, 1.2f};	//�G�l�~�[�̏���Scale
			static const int CALC_LINEHITMODEL_INTERVAL = 15;	//���C���΂��Ԋu
			static const float ENEMY_SEARCH_DIS = 3000.0f;	//�G�l�~�[���v���C���[�𔭌��ł��鋗��
		}

		namespace nsEnemyMoveConstant
		{
			static const float ENEMY_WALK_SPEED = 4.0f;	//�G�l�~�[�̕�������
			static const float ENEMY_DASH_SPEED = 16.0f;//�G�l�~�[�̑��鑬��
			static const float ENEMY_SLOWWALK_SPEED = 2.0f;	//�G�l�~�[�̒x�������̑���
			static const float ENEMY_MOVE_FRICTION = 0.02f;	//�G�l�~�[�̓����Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;	//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��
		
			static const int PATH_FINDING_INTERVAL = 5;	//�o�H�T�����s���Ԋu

			static const int ENEMY_WALK_FOOTSTEP_INTERVAL = 45;	//�G�l�~�[�̕��s���̑����̊Ԋu
			static const int ENEMY_SLOWWALK_FOOTSTEP_INTERVAL = 140;	//�G�l�~�[�̒x�������̑����̊Ԋu
			static const int ENEMY_DASH_FOOTSTEP_INTERVAL = 20; //�G�l�~�[�̑��s���̑����̊Ԋu
		}

		namespace nsEnemySearchPlayerConstant
		{
		}

		namespace nsEnemyChaseConstant
		{
			static const float ENEMY_CAN_ATTACK_DIS = 300.0f;	//�G�l�~�[���U���Ɉڍs���鋗��
		}

		namespace nsEnemyAttackConstant
		{
			static const int ATTACKMOTION_TIME = 61 * 3;	//�U���s�������鎞��(�A�j���[�V�����̎���)
			static const int ATTACKMOTION_HIT_START_TIME = 23 * 2;	//�U�����[�V�����̍U�����肪�n�܂鎞�ԁB
			static const int ATTACKMOTION_HIT_END_TIME = 26 * 2;	//�U�����[�V�����̍U�����肪�I��鎞�ԁB
			static const int ATTACKMOTION_HIT_DOT = 0.2;	//�U������͈̔�(����)
			static const int ATTACKMOTION_HIT_DIS = 200.0f;	//�U������̋���
		
			static const int BITING_TIME = 1000; //�G�l�~�[�Ɋ��݂��ꂽ�����鎞��
			static const int BITEANIM_BITE_TIMING = 20; //�A�j���[�V�����ŃG�l�~�[�����݂��^�C�~���O
			static const int BITE_DAMAGE = 40;			//���݂��̃_���[�W
		}

		namespace nsEnemyAnimConstant
		{
			
		}

		namespace nsEnemyStressConstant
		{
			static const int MAX_STRESS_NUM = 500;	//�G�l�~�[�̃X�g���X�l�̍ő�l
			static const int SUB_STRESS_SPEED = 1;	//�X�g���X�����鑬�x
		}
	}
}