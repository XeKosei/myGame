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
		//�V�����X�|�b�g���C�g�����ꂽ���Ƃ����C�g�}�l�[�W���[�ɋ�����B
		LightManager::GetInstance()->AddNewSpotLight(GetLigData());
		//�X�|�b�g���C�g�ɔԍ���t����B
		m_spotLigNum = LightManager::GetInstance()->GetNewSpotLigNum();
		//���C�g�}�l�[�W���[���Ŕԍ����Ǘ��ł���悤�ɁA�X�|�b�g���C�g�̔ԍ��̃A�h���X�����C�g�}�l�[�W���ɑ���B
		LightManager::GetInstance()->SetSpotLigNum(&m_spotLigNum);

		return true;
	}

	void SpotLight::Update()
	{
		LightManager::GetInstance()->UpdateSpotLight(m_spotLigNum, GetLigData());
	}
}