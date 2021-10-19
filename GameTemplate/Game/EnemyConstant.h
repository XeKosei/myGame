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

		}

		namespace nsEnemyChaseConstant
		{
			static const float ENEMY_WALK_SPEED = 500.0f;	//�G�l�~�[�̕�������
			static const float ENEMY_DASH_SPEED = ENEMY_WALK_SPEED * 1.5f;//�G�l�~�[�̑��鑬��
			static const float ENEMY_MOVE_FRICTION = 0.2f;	//�G�l�~�[�̓����Ƃ��̖��C
			static const float GRAVITY_SPEED = 9.8f * 0.1f;	//�����X�s�[�h
			static const float GRAVITY_INDEX = 1.2f;		//�����X�s�[�h�ɂ�����w��

			static const float ENEMY_CAN_ATTACK_DIS = 50.0f;	//�G�l�~�[���U���Ɉڍs���鋗��
		}

		namespace nsEnemyAttackConstant
		{
			
		}
	}
}