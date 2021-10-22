#include "stdafx.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsBackGround
	{
		bool BackGround::Start()
		{
			m_stageModel = NewGO<SkinModelRender>(0);
			m_stageModel->Init("Assets/modelData/StageTest.tkm");
			//m_stageModel->SetShadowCasterFlag(false);
			//ステージのモデルの静的物理オブジェクトを作成       
			m_physicsStaticObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModel().GetWorldMatrix());
			return true;
		}

		void BackGround::Update()
		{

		}
	}
}