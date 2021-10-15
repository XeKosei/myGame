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
			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks", animationClips, enAnimationClip_num);
			m_enemyModel->SetPosition(Vector3::Zero);
			//�A�j���[�V����
			animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			animationClips[enAnimationClip_Run].SetLoopFlag(true);	//���[�v���[�V�����ɂ���B

			//�L�����R����ݒ�
			m_charaCon.Init(
				ENEMY_MODEL_WIDTH,	//���a
				ENEMY_MODEL_HEIGHT,	//����
				Vector3::Zero//�����ʒu
			);
			
			//m_enemyModel->SetAnimationSpeed(1.0f);

			//�G�l�~�[�֘A�̃C���X�^���X���쐬
			m_enemyMove = NewGO<EnemyMove>(0);
			m_enemyMove->SetEnemy(this);
			m_enemyState = NewGO<EnemyState>(0);
			m_enemyState->SetEnemy(this);
			m_enemyAttack = NewGO<EnemyAttack>(0);
			m_enemyAttack->SetEnemy(this);

			return true;
		}
		void Enemy::Update()
		{
			m_enemyModel->PlayAnimation(enAnimationClip_Run);
			
			//�G�l�~�[�֘A�̏���
			m_enemyMove->ExecuteUpdate();
			m_enemyState->ExecuteUpdate();
			m_enemyAttack->ExecuteUpdate();
		}
	}
}