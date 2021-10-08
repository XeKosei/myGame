#include "stdafx.h"
#include "BackGround.h"
namespace nsHikageri
{

	bool BackGround::Start()
	{
		m_stageModel = NewGO<SkinModelRender>(0);
		m_stageModel->Init("Assets/modelData/Stage.tkm");
		//m_stageModel->SetShadowCasterFlag(false);
		return true;
	}

	void BackGround::Update()
	{

	}
}