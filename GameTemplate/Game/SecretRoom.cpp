#include "stdafx.h"
#include "SecretRoom.h"
namespace nsHikageri
{
	namespace nsBackGround
	{
		SecretRoom::~SecretRoom()
		{
			DeleteGO(m_secretRoomModel);
			DeleteGO(m_fakeWallModel);
		}

		bool SecretRoom::Start()
		{
			//隠し部屋。
			m_secretRoomModel = NewGO<SkinModelRender>(0);
			m_secretRoomModel->SetMakeSkinModelRenderEX(true);
			m_secretRoomModel->Init("Assets/modelData/SecretRoom.tkm");
			m_secretRoomModel->SetNormalCasterFlag(false);
			m_secretRoomModel->SetShadowCasterFlag(false);
			m_secretRoomModel->SetSpotLightCasterFlag(false);

			//隠し部屋のモデルの静的物理オブジェクトを作成       
			m_physicsStaticObject.CreateFromModel(m_secretRoomModel->GetModel(), m_secretRoomModel->GetModel().GetWorldMatrix());

			//偽の壁。すり抜けることができる。
			m_fakeWallModel = NewGO<SkinModelRender>(0);
			m_fakeWallModel->Init("Assets/modelData/FakeWall.tkm");
	
			return true;
		}

		void SecretRoom::Update()
		{

		}
	}
}