#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		namespace nsEnemyConstant
		{
			static const float ENEMY_MODEL_WIDTH = 20.0f;	//プレイヤーのモデルの横幅
			static const float ENEMY_MODEL_HEIGHT = 20.0f;	//プレイヤーのモデルの高さ
		}
		namespace nsEnemyMoveConstant
		{
			static const float ENEMY_WALK_SPEED = 10.0f;	//エネミーの歩く速さ
			static const float ENEMY_DASH_SPEED = ENEMY_WALK_SPEED * 1.5f;//エネミーの走る速さ
			static const float ENEMY_MOVE_FRICTION = 0.2f;	//エネミーの動くときの摩擦
			static const float GRAVITY_SPEED = 9.8f * 0.1f;	//落下スピード
			static const float GRAVITY_INDEX = 1.2f;		//落下スピードにかける指数
		}

		namespace nsEnemyStateConstant
		{
			static const float ENEMY_CAN_ATTACK_DIS = 50.0f;	//エネミーが攻撃に移行できる距離
		}

		namespace nsEnemyAttackConstant
		{
			
		}
	}
}