#include "stdafx.h"
#include "Enemy.h"
#include "EnemyMove.h"
#include "EnemyConstant.h"
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

			return true;
		}
		void Enemy::Update()
		{
			//�^�[�Q�b�g(��)
			m_targetPos = m_player->GetPosition();
			m_enemyModel->PlayAnimation(enAnimationClip_Run);
			
			//�G�l�~�[�֘A�̏���
			m_enemyMove->ExecuteUpdate();
		}
	}
}