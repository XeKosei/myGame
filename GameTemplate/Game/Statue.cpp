#include "stdafx.h"
#include "Statue.h"
#include "EnemyConstant.h"
namespace nsHikageri
{
	namespace nsBackGround
	{
		Statue::~Statue()
		{
			DeleteGO(m_skinModel);
		}

		bool Statue::Start()
		{
			m_skinModel = NewGO<SkinModelRender>(0);
			m_skinModel->SetMakeSkinModelRenderEX(true);
			m_skinModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks", m_animationClips, enStatueAnimClip_num);
			m_skinModel->SetStoneRenderFlag(true);
			m_skinModel->SetScale(nsEnemy::nsEnemyConstant::INI_ENEMY_SCALE);

			//�X�e�[�W�̃��f���̐ÓI�����I�u�W�F�N�g���쐬       
			m_physicsStaticObject.CreateFromModel(m_skinModel->GetModel(), m_skinModel->GetModel().GetWorldMatrix());

			//�ʒu��ݒ�
			m_skinModel->SetPosition(m_position);

			//��]��ݒ�
			float angle = atan2(m_direction.x, m_direction.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_skinModel->SetRotation(qRot);

			//�ÓI�����I�u�W�F�N�g�̈ʒu�Ɖ�]��ݒ�
			m_physicsStaticObject.SetPositionAndRotation(m_position, qRot);

			m_animationClips[enStatueAnimClip_Idle].Load("Assets/animData/EnemyIdle.tka");
			m_animationClips[enStatueAnimClip_Idle].SetLoopFlag(false);
			m_animationClips[enStatueAnimClip_PreBite].Load("Assets/animData/EnemyBite01.tka");
			m_animationClips[enStatueAnimClip_PreBite].SetLoopFlag(true);	//���[�v���[�V�����ɂ���B
			m_animationClips[enStatueAnimClip_SlowWalk].Load("Assets/animData/EnemySlowWalk.tka");
			m_animationClips[enStatueAnimClip_SlowWalk].SetLoopFlag(true);	//���[�v���[�V�����ɂ���B
			m_animationClips[enStatueAnimClip_Scream].Load("Assets/animData/EnemyScream.tka");
			m_animationClips[enStatueAnimClip_Scream].SetLoopFlag(false);
			m_animationClips[enStatueAnimClip_Bite].Load("Assets/animData/EnemyBite02.tka");
			m_animationClips[enStatueAnimClip_Bite].SetLoopFlag(false);

			m_skinModel->PlayAnimation(m_statueAnimClip);

			return true;
		}

		void Statue::Update()
		{

		}
	}
}