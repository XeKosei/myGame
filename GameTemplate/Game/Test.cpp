#include "stdafx.h"
#include "Test.h"

bool Test::Start()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/Idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);	//ループモーションにする。

	m_skin = NewGO<SkinModelRender>(0);
	m_skin->Init("Assets/modelData/unityChan.tkm","Assets/modelData/unityChan.tks", animationClips, enAnimationClip_num);

	m_skin->SetAnimationSpeed(1.0f);
	m_skin->PlayAnimation(enAnimationClip_Idle);

	return true;
}

void Test::Update()
{
	//TestDirLig();
	TestPointLig();


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
			m_pointLig[m_pointLigNum]->SetPosition(m_pointLigPos);
			m_pointLig[m_pointLigNum]->SetColor({ 1.0f,1.0f,1.0f });
			m_pointLig[m_pointLigNum]->SetRange(1000.0f);
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
			m_pointLigPos.x += g_pad[0]->GetLStickXF();
			m_pointLig[m_pointLigNum - 1]->SetPosition(m_pointLigPos);
		}
		if (g_pad[0]->GetLStickYF())
		{
			m_pointLigPos.y += g_pad[0]->GetLStickYF();
			m_pointLig[m_pointLigNum - 1]->SetPosition(m_pointLigPos);
		}
		if (g_pad[0]->GetRStickYF() != 0.0f)
		{
			m_pointLigPos.z += g_pad[0]->GetRStickYF();
			m_pointLig[m_pointLigNum - 1]->SetPosition(m_pointLigPos);
		}
	}


}