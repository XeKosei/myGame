#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "SecretRoom.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		AbilityManager::~AbilityManager()
		{

		}

		void AbilityManager::Init(FlashLight* flashLight)
		{
			m_flashLight = flashLight;

			m_enemy = FindGO<nsEnemy::Enemy>("enemy");
			m_secretRoom = FindGO<nsBackGround::SecretRoom>("secretRoom");

		}
	}
}