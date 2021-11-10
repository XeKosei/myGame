#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "SecretRoom.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		bool AbilityManager::Start()
		{
			m_enemy = FindGO<nsEnemy::Enemy>("enemy");
			m_secretRoom = FindGO<nsBackGround::SecretRoom>("secretRoom");
			return true;
		}
	}
}