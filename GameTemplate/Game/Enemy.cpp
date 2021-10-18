#include "stdafx.h"
#include "EnemyInclude.h"
#include "Player.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyConstant;

		Enemy::~Enemy()
		{
			DeleteGO(m_enemyModel);
		}
		bool Enemy::Start()
		{
			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks", animationClips, enAnimationClip_num);
			m_enemyModel->SetPosition(Vector3::Zero);
			//アニメーション
			animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			animationClips[enAnimationClip_Run].SetLoopFlag(true);	//ループモーションにする。

			//キャラコンを設定
			m_charaCon.Init(
				ENEMY_MODEL_WIDTH,	//半径
				ENEMY_MODEL_HEIGHT,	//高さ
				Vector3::Zero//初期位置
			);
			
			//m_enemyModel->SetAnimationSpeed(1.0f);

			//エネミー関連のインスタンスを作成
			m_enemySearchPlayer = NewGO<EnemySearchPlayer>(0);
			m_enemySearchPlayer->SetEnemy(this);
			m_enemyChase = NewGO<EnemyChase>(0);
			m_enemyChase->SetEnemy(this);
			m_enemyAttack = NewGO<EnemyAttack>(0);
			m_enemyAttack->SetEnemy(this);

			return true;
		}
		void Enemy::Update()
		{
			m_enemyModel->PlayAnimation(enAnimationClip_Run);
			
			//エネミー関連の処理
			switch (m_enemyStates)
			{
			case enState_SearchPlayer:
				m_enemySearchPlayer->ExecuteUpdate();
				break;
			case enState_Chase:
				//Chase();
				m_enemyChase->ExecuteUpdate();
				break;
			case enState_Attack:
				m_enemyAttack->ExecuteUpdate();
				break;
			default:
				break;
			}
		}
	}
}