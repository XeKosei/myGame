#include "stdafx.h"
#include "Enemy.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		bool Enemy::Start()
		{
			animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			animationClips[enAnimationClip_Run].SetLoopFlag(true);	//ループモーションにする。

			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks", animationClips, enAnimationClip_num);

			m_enemyModel->SetPosition(Vector3::Zero);

			//m_enemyModel->SetAnimationSpeed(1.0f);
			return true;
		}
		void Enemy::Update()
		{
			m_enemyModel->PlayAnimation(enAnimationClip_Run);
		}
	}
}