#include "stdafx.h"
#include "PointLight.h"

PointLight::~PointLight()
{
	LightManager::GetInstance()->RemovePointLight(GetPointLigNum());
}

bool PointLight::Start()
{
	//新しいポイントライトが作られたことをライトマネージャーに教える。
	LightManager::GetInstance()->AddNewPointLight(GetLigData());
	//ポイントライトに番号を付ける。
	m_pointLigNum = LightManager::GetInstance()->GetNewPointLigNum();
	//ライトマネージャー側で番号を管理できるように、ポイントライトの番号のアドレスをライトマネージャに送る。
	LightManager::GetInstance()->SetPointLigNum(&m_pointLigNum);

	return true;
}

void PointLight::Update()
{
	LightManager::GetInstance()->UpdatePointLight(m_pointLigNum, GetLigData());
}