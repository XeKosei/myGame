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
		//�V�����f�B���N�V�������C�g�����ꂽ���Ƃ����C�g�}�l�[�W���[�ɋ�����B
		LightManager::GetInstance()->AddNewDirectionLight(GetLigData());
		//�f�B���N�V�������C�g�ɔԍ���t����B
		m_dirLigNum = LightManager::GetInstance()->GetNewDirLigNum();
		//���C�g�}�l�[�W���[���Ŕԍ����Ǘ��ł���悤�ɁA�f�B���N�V�������C�g�̔ԍ��̃A�h���X�����C�g�}�l�[�W���ɑ���B
		LightManager::GetInstance()->SetDirLigNum(&m_dirLigNum);

		return true;
	}

	void DirectionLight::Update()
	{
		LightManager::GetInstance()->UpdateDirectionLight(m_dirLigNum, GetLigData());
	}
}