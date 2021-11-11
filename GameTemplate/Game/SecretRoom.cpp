#include "stdafx.h"
#include "SecretRoom.h"
namespace nsHikageri
{
	namespace nsBackGround
	{
		bool SecretRoom::Start()
		{
			//�B�������B
			m_secretRoomModel = NewGO<SkinModelRender>(0);
			m_secretRoomModel->SetMakeSkinModelRenderEX(true);
			m_secretRoomModel->Init("Assets/modelData/SecretRoom.tkm");
			//�B�������̃��f���̐ÓI�����I�u�W�F�N�g���쐬       
			m_physicsStaticObject.CreateFromModel(m_secretRoomModel->GetModel(), m_secretRoomModel->GetModel().GetWorldMatrix());

			//�U�̕ǁB���蔲���邱�Ƃ��ł���B
			m_fakeWallModel = NewGO<SkinModelRender>(0);
			m_fakeWallModel->Init("Assets/modelData/FakeWall.tkm");
	
			return true;
		}

		void SecretRoom::Update()
		{

		}
	}
}