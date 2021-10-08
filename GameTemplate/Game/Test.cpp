#include "stdafx.h"
#include "Test.h"

bool Test::Start()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/Idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);	//ループモーションにする。
	animationClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_walk].SetLoopFlag(true);	//ループモーションにする。

	m_skin = NewGO<nsHikageri::SkinModelRender>(0);
	m_skin->Init("Assets/modelData/unityChan.tkm","Assets/modelData/unityChan.tks", animationClips, enAnimationClip_num);
	m_skin->SetPosition(m_skinPos);
	m_skin->SetScale({ 1.0f,1.0f,1.0f });
	m_skin->SetSpotLightCasterFlag(false);
	//m_skin->SetShadowCasterFlag(false);

	//m_skin->SetAnimationSpeed(1.0f);


	m_dirLig[0] = NewGO<nsHikageri::DirectionLight>(0);
	m_dirLig[0]->SetDirection({ -1.0f, -1.0f, -1.0f });
	m_dirLig[0]->SetColor({ 0.5f,0.5f,0.5f });
	m_dirLigNum++;

	m_spotLig[0] = NewGO<nsHikageri::SpotLight>(0);
	m_spotLig[0]->SetPosition(m_skinPos);
	m_spotLig[0]->SetDirection({ -1.0f, 0.0f,0.0f});
	m_spotLig[0]->SetColor({ 10.0f,10.0f,10.0f });
	m_spotLig[m_spotLigNum]->SetRange(1000.0f);
	m_spotLig[m_spotLigNum]->SetAngle(Math::DegToRad(20.0f));
	m_spotLigNum++;

	nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(Math::DegToRad(20.0f) * 2.0f);

	nsHikageri::SkinModelRender* stage = NewGO<nsHikageri::SkinModelRender>(0);
	stage->Init("Assets/modelData/Stage.tkm");
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
	
	Move();
	//Turn();
	CameraMove();
	SpotLightMove();
	//m_skin->PlayAnimation(enAnimationClip_walk);
}

void Test::TestDirLig()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_dirLigNum < 5)
		{
			m_dirLig[m_dirLigNum] = NewGO<nsHikageri::DirectionLight>(0);
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
			m_pointLig[m_pointLigNum] = NewGO<nsHikageri::PointLight>(0);
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
			m_spotLig[m_spotLigNum] = NewGO<nsHikageri::SpotLight>(0);
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

void Test::Move()
{
	m_skinMoveSpeed = { Vector3::Zero };

	m_skinMoveSpeed += g_camera3D->GetRight() * g_pad[0]->GetLStickXF() * 15.0f;
	m_skinMoveSpeed += Cross(g_camera3D->GetRight(), Vector3::AxisY) * g_pad[0]->GetLStickYF() * 15.0f;

	m_skinMoveSpeed.y = 0.0f;

	if (g_pad[0]->IsPress(enButtonRB2))
		m_skinMoveSpeed.y += 10.0f;
	if (g_pad[0]->IsPress(enButtonLB2))
		m_skinMoveSpeed.y -= 10.0f;

	m_skinPos += m_skinMoveSpeed;
	m_skin->SetPosition(m_skinPos);
}

void Test::Turn()
{
	if (g_pad[0]->IsPress(enButtonLB1) == false)
	{
		if (m_skinMoveSpeed.x != 0.0f || m_skinMoveSpeed.z != 0.0f)
		{
			//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
			//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
			//atan2を使用して、角度を求めている。
			//これが回転角度になる。
			float angle = atan2(m_skinMoveSpeed.x, m_skinMoveSpeed.z);
			//atanが返してくる角度はラジアン単位なので
			//SetRotationDegではなくSetRotationを使用する。
			m_skinQRot.SetRotation(Vector3::AxisY, angle);
			m_skin->SetRotation(m_skinQRot);
		}
	}
}

void Test::CameraMove()
{
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	if (g_pad[0]->IsPress(enButtonLB1) == false)
	{
		x += g_pad[0]->GetLStickXF() * 0.5f;
	}

	m_cameraDir += g_camera3D->GetRight() * x * 0.05f;
	m_cameraDir += g_camera3D->GetUp() * y * 0.05f;
	m_cameraDir.Normalize();

	//Quaternion cameraQRot;
	//cameraQRot.SetRotationDeg(Vector3::AxisY, 5.0f * x);
	//cameraQRot.Apply(m_toCameraPos);
	////X軸回りの回転
	//Vector3 axisX = { Vector3::Zero };
	//axisX.Cross(Vector3::AxisY, m_toCameraPos);
	//axisX.Normalize();
	//cameraQRot.SetRotationDeg(axisX, 5.0f * y);
	//cameraQRot.Apply(m_toCameraPos);

	////カメラリセット1
	//if (g_pad[0]->IsTrigger(enButtonLB1)) {
	//	m_toCameraPos = { 0.0f, 200.0f, 0.0f };
	//	cameraQRot = m_skinQRot;
	//	cameraQRot.Apply(m_toCameraPos);
	//}

	///*if (g_pad[0]->IsPress(enButtonRB3))
	//	m_toCameraPos += g_camera3D->GetForward() * 15.0f;
	//if (g_pad[0]->IsPress(enButtonLB3))
	//	m_toCameraPos -= g_camera3D->GetForward() * 15.0f;*/

	//m_cameraPos = m_skinPos + m_toCameraPos;

	m_cameraPos = m_skinPos + Cross(g_camera3D->GetRight(), Vector3::AxisY) * 5.0f;
	m_cameraPos.y += 200.0f;
	Vector3 cameraTarget = m_cameraDir * 1000.0f + m_skinPos;

	g_camera3D->SetPosition(m_cameraPos);
	g_camera3D->SetTarget(cameraTarget);
}

void Test::SpotLightMove()
{
	//位置を設定
	m_spotLigPos = { m_skinPos.x + 1.0f, m_skinPos.y + 200.0f, m_skinPos.z };

	m_spotLig[0]->SetPosition(m_spotLigPos);
	nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_spotLigPos);

	//向きを設定
	if (g_pad[0]->IsPress(enButtonLB1) == false)
	{
		m_spotLigDir = g_camera3D->GetForward();
		m_spotLigDir.y = 0.0f;
		m_spotLigDir.Normalize();
	}
	else
	{
		m_spotLigDir = g_camera3D->GetForward();
		/*Vector3 dir = m_spotLigDir;
		dir += Cross(dir, Vector3::AxisY) * g_pad[0]->GetLStickXF() * 0.1f * -1.0f;
		dir.y +=  g_pad[0]->GetLStickYF() * 0.1f;
		dir.Normalize();
		m_spotLigDir = dir;*/
	}

	Vector3 spotLigTarget = m_spotLigPos + m_spotLigDir * 100.0f;
	nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(spotLigTarget);
	m_spotLig[0]->SetDirection({ m_spotLigDir });
}
