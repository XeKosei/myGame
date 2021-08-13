#include "stdafx.h"
#include "PointLight.h"

PointLight::~PointLight()
{
	LightManager::GetInstance()->RemovePointLight(GetPointLigNum());
}

bool PointLight::Start()
{
	//�V�����|�C���g���C�g�����ꂽ���Ƃ����C�g�}�l�[�W���[�ɋ�����B
	LightManager::GetInstance()->AddNewPointLight(GetLigData());
	//�|�C���g���C�g�ɔԍ���t����B
	m_pointLigNum = LightManager::GetInstance()->GetNewPointLigNum();
	//���C�g�}�l�[�W���[���Ŕԍ����Ǘ��ł���悤�ɁA�|�C���g���C�g�̔ԍ��̃A�h���X�����C�g�}�l�[�W���ɑ���B
	LightManager::GetInstance()->SetPointLigNum(&m_pointLigNum);

	return true;
}

void PointLight::Update()
{
	LightManager::GetInstance()->UpdatePointLight(m_pointLigNum, GetLigData());
}