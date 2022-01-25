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
			m_skinModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks", m_animationClips, enAnimationClip_num);
			m_skinModel->SetStoneRenderFlag(true);
			m_skinModel->SetScale(nsEnemy::nsEnemyConstant::INI_ENEMY_SCALE);

			//ステージのモデルの静的物理オブジェクトを作成       
			m_physicsStaticObject.CreateFromModel(m_skinModel->GetModel(), m_skinModel->GetModel().GetWorldMatrix());

			//位置を設定
			m_skinModel->SetPosition(m_position);

			//回転を設定
			float angle = atan2(m_direction.x, m_direction.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_skinModel->SetRotation(qRot);

			//静的物理オブジェクトの位置と回転を設定
			m_physicsStaticObject.SetPositionAndRotation(m_position, qRot);

			m_animationClips[enAnimationClip_Idle].Load("Assets/animData/EnemyIdle.tka");
			m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
			m_animationClips[enAnimationClip_Run].Load("Assets/animData/EnemyRun.tka");
			m_animationClips[enAnimationClip_Run].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enAnimationClip_SlowWalk].Load("Assets/animData/EnemySlowWalk.tka");
			m_animationClips[enAnimationClip_SlowWalk].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enAnimationClip_Scream].Load("Assets/animData/EnemyScream.tka");
			m_animationClips[enAnimationClip_Scream].SetLoopFlag(false);
			m_animationClips[enAnimationClip_Bite].Load("Assets/animData/EnemyBite02.tka");
			m_animationClips[enAnimationClip_Bite].SetLoopFlag(false);

			m_skinModel->PlayAnimation(enAnimationClip_Idle);

			return true;
		}

		void Statue::Update()
		{

		}
	}
}