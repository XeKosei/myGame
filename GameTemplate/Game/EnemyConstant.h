#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		namespace nsEnemyConstant
		{
			static const float ENEMY_MODEL_WIDTH = 20.0f;	//�v���C���[�̃��f���̉���
			static const float ENEMY_MODEL_HEIGHT = 20.0f;	//�v���C���[�̃��f���̍���
			static const Vector3 INI_ENEMY_POSITION = {Vector3::Zero};
			static const Vector3 INI_ENEMY_DIRECTION = { 0.0f,0.0f,1.0f };
		}

		namespace nsEnemySearchPlayerConstant
		{
			static const float ENEMY_WALK_SPEED = 3.0f;	//�G�l�~�[�̕�������
		}

		namespace nsEnemyChaseConstant
		{
			static const float ENEMY_DASH_SPEED = 800.0f;//�G�l�~�[�̑��鑬��
			static const float ENEMY_MOVE_FRICTION = 0.2f;	//�G�l�~�[�̓����Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;	//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��

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
			static const int BITE_DAMAGE = 20;			//���݂��̃_���[�W(�A���q�b�g����)
		}

		namespace nsEnemyAnimConstant
		{
			
		}
	}
}