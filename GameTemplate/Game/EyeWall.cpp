#include "stdafx.h"
#include "GimmickInclude.h"
namespace nsHikageri
{
	namespace nsGimmick
	{
		using namespace nsEyeWallConstant;

		EyeWall::~EyeWall()
		{
			DeleteGO(m_eyeWallModel);
		}

		bool EyeWall::Start()
		{
			m_eyeWallModel = NewGO<SkinModelRender>(0);
			m_eyeWallModel->Init("Assets/modelData/EyeWall.tkm");
			//モデルの静的物理オブジェクトを作成       
			m_physicsStaticObject.CreateFromModel(m_eyeWallModel->GetModel(), m_eyeWallModel->GetModel().GetWorldMatrix());
			
			//位置
			m_eyeWallModel->SetPosition(m_position);
			//回転
			m_direction.Normalize();
			float angle = atan2(m_direction.x, m_direction.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_eyeWallModel->SetRotation(qRot);
			//スケール
			m_eyeWallModel->SetScale(m_scale);

			//静的物理オブジェクトの位置と回転を設定
			m_physicsStaticObject.SetPositionAndRotation(m_position, qRot);

			//Disapper()関連
			m_disapperSpeed = DISAPPER_SPEED;
			m_disapperMoveCount = INI_DESAPPER_INTERVAL;

			return true;
		}
		void EyeWall::Update()
		{
			//trueなら消える
			if (m_disapperFlag)
			{
				Disapper();
			}
		}
		void EyeWall::Disapper()
		{
			m_disapperMoveCount--;

			if (m_disapperMoveCount == 0)
			{
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/EyeWall.wav");
				ss->Play(false);
			}
			if (m_disapperMoveCount <= 0)
			{
				m_disapperSpeed += m_disapperSpeed * DISAPPER_SPEED_MUL_VALUE;
				m_scale.y -= m_disapperSpeed;
				m_eyeWallModel->SetScale(m_scale);
			}
			if(m_scale.y <= 0.0f)
			{
				DeleteGO(this);
			}
		}
	}
}