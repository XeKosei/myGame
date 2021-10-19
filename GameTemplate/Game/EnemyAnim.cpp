#include "stdafx.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		bool EnemyAnim::Start()
		{
			m_animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			m_animationClips[enAnimationClip_Run].SetLoopFlag(true);	//���[�v���[�V�����ɂ���B

			return true;
		}
		void EnemyAnim::ExecuteUpdate()
		{
			m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Run);
		}
	}
}