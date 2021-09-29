#include "stdafx.h"
#include "Test.h"

bool Test::Start()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/Idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);	//ループモーションにする。
	animationClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_walk].SetLoopFlag(true);	//ループモーションにする。

	m_skin = NewGO<SkinModelRender>(0);
	m_skin->Init("Assets/modelData/unityChan.tkm","Assets/modelData/unityChan.tks", animationClips, enAnimationClip_num);
	m_skin->SetPosition(m_skinPos);
	m_skin->SetScale({ 1.0f,1.0f,1.0f });
	//m_skin->SetShadowCasterFlag(false);

	//m_skin->SetAnimationSpeed(1.0f);


	m_dirLig[0] = NewGO<DirectionLight>(0);
	m_dirLig[0]->SetDirection({ -1.0f, -1.0f, -1.0f });
	m_dirLig[0]->SetColor({ 0.5f,0.5f,0.5f });
	m_dirLigNum++;

	m_spotLig[0] = NewGO<SpotLight>(0);
	m_spotLig[0]->SetPosition(m_skinPos);
	m_spotLig[0]->SetDirection({ -1.0f, 0.0f,0.0f});
	m_spotLig[0]->SetColor({ 10.0f,10.0f,10.0f });
	m_spotLig[m_spotLigNum]->SetRange(1000.0f);
	m_spotLig[m_spotLigNum]->SetAngleDeg(20.0f);
	m_spotLigNum++;

	SkinModelRender* stage = NewGO<SkinModelRender>(0);
	stage->Init("Assets/modelData/BuildingStage.tkm");
	stage->SetShadowCasterFlag(false);
	stage->SetPosition({0.0f,10.0f, 0.0f});
	stage->SetScale({ 1.0f,1.0f,1.0f });

	return true;
}

void Test::Update()
{
	TestDirLig();
	//TestPointLig();
	//TestSpotLig();

	if (g_pad[0]->IsPress(enButtonRight))
		m_skinPos.x += 10.0f;
	if (g_pad[0]->IsPress(enButtonLeft))
		m_skinPos.x -= 10.0f;
	if (g_pad[0]->IsPress(enButtonUp))
		m_skinPos.z += 10.0f;
	if (g_pad[0]->IsPress(enButtonDown))
		m_skinPos.z -= 10.0f;
	if (g_pad[0]->IsPress(enButtonLB2))
		m_skinPos.y += 10.0f;
	if (g_pad[0]->IsPress(enButtonRB2))
		m_skinPos.y -= 10.0f;

	m_skin->SetPosition(m_skinPos);

	m_cameraPos.x += g_pad[0]->GetRStickXF() * 30.0f;
	m_cameraPos.z += g_pad[0]->GetRStickYF() * 30.0f;

	g_camera3D->SetPosition(m_cameraPos);

	m_spotLig[0]->SetPosition({ m_skinPos.x - 40.0f, m_skinPos.y, m_skinPos.z });
	//m_skin->PlayAnimation(enAnimationClip_walk);

	m_spotLigDir.y += g_pad[0]->GetLStickXF() * 10.0f;
	m_spotLig[0]->SetDirection({ m_skinPos.x - 100.0f, m_skinPos.y + m_spotLigDir.y, m_skinPos.z });
	LightManager::GetInstance()->SetSpotLightCameraPosition({ m_skinPos.x - 40.0f, m_skinPos.y, m_skinPos.z });
	LightManager::GetInstance()->SetSpotLightCameraTarget({m_skinPos.x - 100.0f, m_skinPos.y + m_spotLigDir.y, m_skinPos.z});
}

void Test::TestDirLig()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_dirLigNum < 5)
		{
			m_dirLig[m_dirLigNum] = NewGO<DirectionLight>(0);
			m_dirLig[m_dirLigNum]->SetDirection({ -1.0f, -1.0f, -1.0f });
			m_dirLig[m_dirLigNum]->SetColor({ 1.0f,1.0f,1.0f });

			m_dirLigNum++;
		}
	}

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		if (m_dirLigNum > 0)
		{
			DeleteGO(m_dirLig[m_dirLigNum - 1]);

			m_dirLigNum--;
		}
	}
}

void Test::TestPointLig()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_pointLigNum < 20)
		{
			m_pointLig[m_pointLigNum] = NewGO<PointLight>(0);
			m_pointLig[m_pointLigNum]->SetPosition(m_ligPos);
			m_pointLig[m_pointLigNum]->SetColor({ 1.0f,1.0f,1.0f });
			m_pointLig[m_pointLigNum]->SetRange(5000.0f);
			m_pointLigNum++;
		}
	}

	if (g_pad[0]->IsTrigger(enButtonB) != 0.0f)
	{
		if (m_pointLigNum > 0)
		{
			DeleteGO(m_pointLig[m_pointLigNum - 1]);

			m_pointLigNum--;
		}
	}

	if (m_pointLigNum > 0)
	{
		if (g_pad[0]->GetLStickXF() != 0.0f)
		{
			m_ligPos.x += g_pad[0]->GetLStickXF();
			m_pointLig[m_pointLigNum - 1]->SetPosition(m_ligPos);
		}
		if (g_pad[0]->GetLStickYF())
		{
			m_ligPos.y += g_pad[0]->GetLStickYF();
			m_pointLig[m_pointLigNum - 1]->SetPosition(m_ligPos);
		}
		if (g_pad[0]->GetRStickYF() != 0.0f)
		{
			m_ligPos.z += g_pad[0]->GetRStickYF();
			m_pointLig[m_pointLigNum - 1]->SetPosition(m_ligPos);
		}
	}
}

void Test::TestSpotLig()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_spotLigNum < 20)
		{
			m_spotLig[m_spotLigNum] = NewGO<SpotLight>(0);
			m_spotLig[m_spotLigNum]->SetPosition(m_ligPos);
			m_spotLig[m_spotLigNum]->SetColor({ 1.0f,1.0f,1.0f });
			m_spotLig[m_spotLigNum]->SetRange(1000.0f);
			m_spotLig[m_spotLigNum]->SetDirection({1.0f,0.0f,0.0f});
			m_spotLig[m_spotLigNum]->SetAngleDeg(90.0f);

			m_spotLigNum++;
		}
	}

	if (g_pad[0]->IsTrigger(enButtonB) != 0.0f)
	{
		if (m_spotLigNum > 0)
		{
			DeleteGO(m_spotLig[m_spotLigNum - 1]);

			m_spotLigNum--;
		}
	}

	if (m_spotLigNum > 0)
	{
		if (g_pad[0]->GetLStickXF() != 0.0f)
		{
			m_ligPos.x += g_pad[0]->GetLStickXF();
			m_spotLig[m_spotLigNum - 1]->SetPosition(m_ligPos);
		}
		if (g_pad[0]->GetLStickYF())
		{
			m_ligPos.y += g_pad[0]->GetLStickYF();
			m_spotLig[m_spotLigNum - 1]->SetPosition(m_ligPos);
		}
		if (g_pad[0]->GetRStickYF() != 0.0f)
		{
			m_ligPos.z += g_pad[0]->GetRStickYF();
			m_spotLig[m_spotLigNum - 1]->SetPosition(m_ligPos);
		}
	}
}