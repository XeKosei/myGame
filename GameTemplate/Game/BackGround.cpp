#include "stdafx.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsBackGround
	{
		BackGround::~BackGround()
		{
			DeleteGO(m_stageModel);
		}

		bool BackGround::Start()
		{
			m_stageModel = NewGO<SkinModelRender>(0);
			m_stageModel->Init("Assets/modelData/Stage.tkm");
			//m_stageModel->SetShadowCasterFlag(false);
			//�X�e�[�W�̃��f���̐ÓI�����I�u�W�F�N�g���쐬       
			m_physicsStaticObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModel().GetWorldMatrix());
			return true;
		}

		void BackGround::Update()
		{

		}
	}
}