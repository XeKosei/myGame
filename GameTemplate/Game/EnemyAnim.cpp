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
			m_animationClips[enAnimationClip_SlowWalk].Load("Assets/animData/EnemySlowWalk.tka");
			m_animationClips[enAnimationClip_SlowWalk].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enAnimationClip_Attack].Load("Assets/animData/EnemyBite.tka");
			m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);	
			m_animationClips[enAnimationClip_Scream].Load("Assets/animData/EnemyScream.tka");
			m_animationClips[enAnimationClip_Scream].SetLoopFlag(false);
			m_animationClips[enAnimationClip_Flinch].Load("Assets/animData/EnemyFlinch.tka");
			m_animationClips[enAnimationClip_Flinch].SetLoopFlag(false);
			m_animationClips[enAnimationClip_Petrifaction].Load("Assets/animData/EnemyPetrifaction.tka");
			m_animationClips[enAnimationClip_Petrifaction].SetLoopFlag(false);
			m_animationClips[enAnimationClip_Suffer].Load("Assets/animData/EnemySuffer.tka");
			m_animationClips[enAnimationClip_Suffer].SetLoopFlag(false);
			m_animationClips[enAnimationClip_PreBite].Load("Assets/animData/EnemyBite01.tka");
			m_animationClips[enAnimationClip_PreBite].SetLoopFlag(false);
			m_animationClips[enAnimationClip_Bite].Load("Assets/animData/EnemyBite02.tka");
			m_animationClips[enAnimationClip_Bite].SetLoopFlag(false);	
			m_animationClips[enAnimationClip_EndBite].Load("Assets/animData/EnemyBite03.tka");
			m_animationClips[enAnimationClip_EndBite].SetLoopFlag(false);	

			return true;
		}
		void EnemyAnim::ExecuteUpdate()
		{
			switch (m_enemy->GetEnemyState())
			{
			case Enemy::enState_SearchPlayer:
				if (m_enemy->GetEnemyMove()->GetSlowMoveFlag())	
					m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_SlowWalk);
				else
					m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Walk);
				break;
			case Enemy::enState_Chase:	
				if (m_enemy->GetEnemyMove()->GetSlowMoveFlag())
					m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_SlowWalk);
				else 
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
			case Enemy::enState_Scream:
				m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Scream);
				break;
			case Enemy::enState_Flinch:
				m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Flinch);
				break;
			case Enemy::enState_Petrifaction:
				m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Petrifaction);
				break;
			case Enemy::enState_Suffer :
				m_enemy->GetEnemyModel()->PlayAnimation(enAnimationClip_Suffer);
				break;
			default:
				break;
			}
		}
	}
}