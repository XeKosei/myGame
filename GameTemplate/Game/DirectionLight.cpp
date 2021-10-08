#include "stdafx.h"
#include "DirectionLight.h"
namespace nsHikageri
{
	DirectionLight::~DirectionLight()
	{
		LightManager::GetInstance()->RemoveDirectionLight(GetDirLigNum());
	}

	bool DirectionLight::Start()
	{
		//新しいディレクションライトが作られたことをライトマネージャーに教える。
		LightManager::GetInstance()->AddNewDirectionLight(GetLigData());
		//ディレクションライトに番号を付ける。
		m_dirLigNum = LightManager::GetInstance()->GetNewDirLigNum();
		//ライトマネージャー側で番号を管理できるように、ディレクションライトの番号のアドレスをライトマネージャに送る。
		LightManager::GetInstance()->SetDirLigNum(&m_dirLigNum);

		return true;
	}

	void DirectionLight::Update()
	{
		LightManager::GetInstance()->UpdateDirectionLight(m_dirLigNum, GetLigData());
	}
}