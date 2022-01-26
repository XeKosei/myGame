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

			
			//位置を設定
			m_skinModel->SetPosition(m_position);

			//回転を設定
			float angle = atan2(m_direction.x, m_direction.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_skinModel->SetRotation(qRot);

			//キャラコンを設定
			m_charaCon.Init(
				nsEnemy::nsEnemyConstant::ENEMY_MODEL_WIDTH,	//半径
				nsEnemy::nsEnemyConstant::ENEMY_MODEL_HEIGHT,	//高さ
				m_position//初期位置
			);

			m_animationClips[enStatueAnimClip_Idle].Load("Assets/animData/EnemyIdle.tka");
			m_animationClips[enStatueAnimClip_Idle].SetLoopFlag(false);
			m_animationClips[enStatueAnimClip_PreBite].Load("Assets/animData/EnemyBite01.tka");
			m_animationClips[enStatueAnimClip_PreBite].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enStatueAnimClip_SlowWalk].Load("Assets/animData/EnemySlowWalk.tka");
			m_animationClips[enStatueAnimClip_SlowWalk].SetLoopFlag(true);	//ループモーションにする。
			m_animationClips[enStatueAnimClip_Scream].Load("Assets/animData/EnemyScream.tka");
			m_animationClips[enStatueAnimClip_Scream].SetLoopFlag(false);
			m_animationClips[enStatueAnimClip_Bite].Load("Assets/animData/EnemyWalk.tka");
			m_animationClips[enStatueAnimClip_Bite].SetLoopFlag(false);

			m_skinModel->PlayAnimation(m_statueAnimClip);

			return true;
		}

		void Statue::Update()
		{

		}
	}
}