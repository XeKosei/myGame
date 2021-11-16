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

			//�v���C���[���߂��ɂ���Ȃ�΁A
			if ((playerPos - m_position).Length() <= CHANDELIER_LIGHT_RANGE
				&& m_enemy->GetEnemyState() != nsEnemy::Enemy::enState_Chase)
			{
				//�v���C���[�͈��S�ł���B
				m_player->GetPlayerSanity()->SetReliefFlag(true);
			}

			//�G�l�~�[���߂��ɂ���Ȃ�΁A
			if ((enemyPos - m_position).Length() <= CHANDELIER_LIGHT_RANGE)
			{
				m_enemy->GetEnemyMove()->SetSlowMoveFlag(true);
				if (m_enemy->GetEnemyState() == nsEnemy::Enemy::enState_Chase)
				{
					m_enemy->GetEnemyStress()->AddStress(CHANDELIER_ADD_STRESS_SPEED);
				}
			}
		}
	}
}