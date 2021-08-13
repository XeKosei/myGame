#include "stdafx.h"
#include "Test.h"

bool Test::Start()
{
	m_skin = NewGO<SkinModelRender>(0);
	m_skin->Init("Assets/modelData/unityChan.tkm");

	return true;
}

void Test::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_dirLigNum < 4)
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
			DeleteGO(m_dirLig[m_dirLigNum]);

			m_dirLigNum--;
		}
	}


}