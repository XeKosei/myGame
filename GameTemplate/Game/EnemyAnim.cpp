#include "stdafx.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyAnimConstant;

		bool EnemyAnim::Start()
		{
			m_animationClips[enAnimationClip_Idle].Load("Assets/animData/EnemyIdle.tka");
			m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enAnimationClip_Walk].Load("Assets/animData/EnemyWalk.tka");
			m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			m_animationClips[enAnimationClip_Run].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enAnimationClip_Attack].Load("Assets/animData/EnemyBite.tka");
			m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);	//ループモーションにする。
			m_animationClips[enAnimationClip_Scream].Load("Assets/animData/EnemyScream.tka");
			m_animationClips[enAnimationClip_Scream].SetLoopFlag(false);	//ループモーションにする。
			m_animationClips[enAnimationClip_PreBite].Load("Assets/animData/EnemyBite01.tka");
			m_animationClips[enAnimationClip_PreBite].SetLoopFlag(false);	//ループモーションにする。
			m_animationClips[enAnimationClip_Bite].Load("Assets/animData/EnemyBite02.tka");
			m_animationClips[enAnimationClip_Bite].SetLoopFlag(false);	//ループモーションにする。
			m_animationClips[enAnimationClip_EndBite].Load("Assets/animData/EnemyBite03.tka");
			m_animationClips[enAnimationClip_EndBite].SetLoopFlag(false);	//ループモーションにする。

			return true;
		}
		void EnemyAnim::ExecuteUpdate()
		{
			switch (m_enemy->GetEnemyState())
			{
			case Enemy::enState_SearchPlayer:
				m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Walk);
				break;
			case Enemy::enState_Chase:
				m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Run);
				break;
			case Enemy::enState_Attack:
				//m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Attack);
				switch (m_enemy->GetEnemyAttack()->GetBiteState())
				{
				case EnemyAttack::enBiteState_PreBite:
					m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_PreBite);
					break;
				case EnemyAttack::enBiteState_Bite:
					m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Bite);
					break;
				case EnemyAttack::enBiteState_EndBite:
					m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_EndBite);
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}
}