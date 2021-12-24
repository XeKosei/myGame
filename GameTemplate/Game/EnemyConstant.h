#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		namespace nsEnemyConstant
		{
			static const float ENEMY_MODEL_WIDTH = 10.0f;	//プレイヤーのモデルの横幅
			static const float ENEMY_MODEL_HEIGHT = 120.0f;	//プレイヤーのモデルの高さ
			static const Vector3 INI_ENEMY_SCALE = {1.2f, 1.2f, 1.2f};	//エネミーの初期Scale
			static const int CALC_LINEHITMODEL_INTERVAL = 15;	//レイを飛ばす間隔
			static const float ENEMY_SEARCH_DIS = 3000.0f;	//エネミーがプレイヤーを発見できる距離
		}

		namespace nsEnemyMoveConstant
		{
			static const float ENEMY_WALK_SPEED = 4.0f;	//エネミーの歩く速さ
			static const float ENEMY_DASH_SPEED = 16.0f;//エネミーの走る速さ
			static const float ENEMY_SLOWWALK_SPEED = 2.0f;	//エネミーの遅い歩きの速さ
			static const float ENEMY_MOVE_FRICTION = 0.02f;	//エネミーの動くときの摩擦
			static const float GRAVITY_SPEED = 9.8f * 0.1f;	//落下スピード
			static const float GRAVITY_INDEX = 1.2f;		//落下スピードにかける指数
		
			static const int PATH_FINDING_INTERVAL = 5;	//経路探索を行う間隔

			static const int ENEMY_WALK_FOOTSTEP_INTERVAL = 45;	//エネミーの歩行時の足音の間隔
			static const int ENEMY_SLOWWALK_FOOTSTEP_INTERVAL = 140;	//エネミーの遅い歩きの足音の間隔
			static const int ENEMY_DASH_FOOTSTEP_INTERVAL = 20; //エネミーの走行時の足音の間隔
		}

		namespace nsEnemySearchPlayerConstant
		{
		}

		namespace nsEnemyChaseConstant
		{
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
			static const int BITE_DAMAGE = 40;			//噛みつきのダメージ
		}

		namespace nsEnemyAnimConstant
		{
			
		}

		namespace nsEnemyStressConstant
		{
			static const int MAX_STRESS_NUM = 500;	//エネミーのストレス値の最大値
			static const int SUB_STRESS_SPEED = 1;	//ストレスが減る速度
		}
	}
}