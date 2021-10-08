#include "stdafx.h"
#include "SpotLight.h"
namespace nsHikageri
{
	SpotLight::~SpotLight()
	{
		LightManager::GetInstance()->RemoveSpotLight(GetSpotLigNum());
	}

	bool SpotLight::Start()
	{
		//新しいスポットライトが作られたことをライトマネージャーに教える。
		LightManager::GetInstance()->AddNewSpotLight(GetLigData());
		//スポットライトに番号を付ける。
		m_spotLigNum = LightManager::GetInstance()->GetNewSpotLigNum();
		//ライトマネージャー側で番号を管理できるように、スポットライトの番号のアドレスをライトマネージャに送る。
		LightManager::GetInstance()->SetSpotLigNum(&m_spotLigNum);

		return true;
	}

	void SpotLight::Update()
	{
		LightManager::GetInstance()->UpdateSpotLight(m_spotLigNum, GetLigData());
	}
}