#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		namespace nsEnemyConstant
		{
			static const float ENEMY_MODEL_WIDTH = 20.0f;	//プレイヤーのモデルの横幅
			static const float ENEMY_MODEL_HEIGHT = 20.0f;	//プレイヤーのモデルの高さ
			static const Vector3 INI_ENEMY_POSITION = {Vector3::Zero};
			static const Vector3 INI_ENEMY_DIRECTION = { 0.0f,0.0f,1.0f };
		}

		namespace nsEnemySearchPlayerConstant
		{
			static const float ENEMY_WALK_SPEED = 3.0f;	//エネミーの歩く速さ
		}

		namespace nsEnemyChaseConstant
		{
			static const float ENEMY_DASH_SPEED = 800.0f;//エネミーの走る速さ
			static const float ENEMY_MOVE_FRICTION = 0.2f;	//エネミーの動くときの摩擦
			static const float GRAVITY_SPEED = 9.8f * 0.1f;	//落下スピード
			static const float GRAVITY_INDEX = 1.2f;		//落下スピードにかける指数

			static const float ENEMY_CAN_ATTACK_DIS = 300.0f;	//エネミーが攻撃に移行する距離
		}

		namespace nsEnemyAttackConstant
		{
			static const int ATTACKMOTION_TIME = 61 * 3;	//攻撃行動をする時間(アニメーションの時間)
			static const int ATTACKMOTION_HIT_START_TIME = 23 * 2;	//攻撃モーションの攻撃判定が始まる時間。
			static const int ATTACKMOTION_HIT_END_TIME = 26 * 2;	//攻撃モーションの攻撃判定が終わる時間。
			static const int ATTACKMOTION_HIT_DOT = 0.2;	//攻撃判定の範囲(内積)
			static const int ATTACKMOTION_HIT_DIS = 200.0f;	//攻撃判定の距離
		
			static const int BITING_TIME = 1000; //エネミーに噛みつかれた続ける時間
			static const int BITEANIM_BITE_TIMING = 20; //アニメーションでエネミーが噛みつくタイミング
			static const int BITE_DAMAGE = 20;			//噛みつきのダメージ(連続ヒットする)
		}

		namespace nsEnemyAnimConstant
		{
			
		}
	}
}