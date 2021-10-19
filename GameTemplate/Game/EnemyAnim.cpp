#include "stdafx.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		bool EnemyAnim::Start()
		{
			m_animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			m_animationClips[enAnimationClip_Run].SetLoopFlag(true);	//ループモーションにする。

			return true;
		}
		void EnemyAnim::ExecuteUpdate()
		{
			m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Run);
		}
	}
}