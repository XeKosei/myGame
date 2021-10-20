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
			//�L�����R����ݒ�
			m_charaCon.Init(
				ENEMY_MODEL_WIDTH,	//���a
				ENEMY_MODEL_HEIGHT,	//����
				INI_ENEMY_POSITION//�����ʒu
			);		

			//�G�l�~�[�֘A�̃C���X�^���X���쐬
			m_enemySearchPlayer = NewGO<EnemySearchPlayer>(0);
			m_enemySearchPlayer->SetEnemy(this);
			m_enemyChase = NewGO<EnemyChase>(0);
			m_enemyChase->SetEnemy(this);
			m_enemyAttack = NewGO<EnemyAttack>(0);
			m_enemyAttack->SetEnemy(this);
			m_enemyAnim = NewGO<EnemyAnim>(0);
			m_enemyAnim->SetEnemy(this);

			//m_enemyStates = enState_SearchPlayer;
			
			//���f�����쐬
			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks",m_enemyAnim->GetAnimationClip(), m_enemyAnim->GetAnimationClipNum());
			m_enemyModel->SetPosition(INI_ENEMY_POSITION);

			return true;
		}
		void Enemy::Update()
		{
			//�G�l�~�[�֘A�̏���
			switch (m_enemyState)
			{
			case enState_SearchPlayer:
				m_enemySearchPlayer->ExecuteUpdate();
				break;
			case enState_Chase:
				m_enemyChase->ExecuteUpdate();
				break;
			case enState_Attack:
				m_enemyAttack->ExecuteUpdate();
				break;
			default:
				break;
			}
			//�A�j���[�V�����Đ�
			m_enemyAnim->ExecuteUpdate();

		}
	}
}