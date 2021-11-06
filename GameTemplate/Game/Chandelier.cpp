#include "stdafx.h"
#include "Chandelier.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h"
#include "GimmickConstant.h"

namespace nsHikageri
{
	namespace nsGimmick
	{
		using namespace nsChandelierConstant;

		bool Chandelier::Start()
		{
			//���f��
			m_chandelierModel = NewGO<SkinModelRender>(0);
			m_chandelierModel->Init("Assets/modelData/chandelier.tkm");
			m_chandelierModel->SetPosition(m_position);

			//�|�C���g���C�g
			m_pointLig = NewGO<PointLight>(0);
			m_pointLig->SetColor({ 10.0f,10.0f,10.0f });
			m_pointLig->SetPosition(m_position);
			m_pointLig->SetRange(CHANDELIER_LIGHT_RANGE);

			return true;
		}

		void Chandelier::Update()
		{
			//�v���C���[�ƃG�l�~�[�̈ʒu
			Vector3 playerPos = m_player->GetPlayerMove()->GetPosition();
			Vector3 enemyPos = m_enemy->GetEnemyMove()->GetPosition();

			//�v���C���[���߂��ɂ���Ȃ�΁ASAN�l��
			if ((playerPos - m_position).Length() <= CHANDELIER_LIGHT_RANGE
				&& (enemyPos - playerPos).Length() >= 1000.0f 
				&& m_enemy->GetEnemyState() != nsEnemy::Enemy::enState_Chase)
			{
				m_player->GetPlayerSanity()->Recovery(1.0f);
			}

			//�G�l�~�[���߂��ɂ���Ȃ�΁A
			if ((enemyPos - m_position).Length() <= CHANDELIER_LIGHT_RANGE)
			{
				m_enemy->GetEnemyMove()->SetSlowMoveFlag(true);
				m_enemy->GetEnemyStress()->AddStress(1);
			}
			else
			{
				m_enemy->GetEnemyMove()->SetSlowMoveFlag(false);
				m_enemy->GetEnemyStress()->SubStress(1);
			}
		}
	}
}