#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"

namespace
{
	//�e���C�g�̍ő吔�@���̐���model.fx�̃��C�g�z��̐��ƈꏏ�ɂ��Ȃ���΂Ȃ�Ȃ�
	const int DIRECTIONLIGHT_NUMBER_MAX = 5;
	const int POINTLIGHT_NUMBER_MAX = 20;
	const int SPOTLIGHT_NUMBER_MAX = 20;
}

class LightManager
{
private:
	LightManager() = default;
	~LightManager() = default;

	static LightManager* m_instance;

	struct LigDatas
	{
		DirLigData directionLight[DIRECTIONLIGHT_NUMBER_MAX];	//�f�B���N�V�������C�g�̃f�[�^�̔z��
		//PointLigData pointLight[POINTLIGHT_NUMBER_MAX];		//�|�C���g���C�g�̃f�[�^�̔z��
		//SpotLigData spotLight[SPOTLIGHT_NUMBER_MAX];			//�X�|�b�g���C�g�̃f�[�^�̔z��
		Vector3 eyePos;					//�J�����̈ʒu
		int directionLightNum = 0;		//�f�B���N�V�������C�g�̐�
		int pointLightNum = 0;			//�|�C���g���C�g�̐�
		int spotLightNum = 0;			//�X�|�b�g���C�g�̐�
	};
	LigDatas m_ligData;					//���C�g�̃f�[�^
	int m_size = sizeof(m_ligData);		//���C�g�̃f�[�^�̃T�C�Y

	//���Ԗڂɍ�������L�^
	int m_directionLigCreateNum = 0;
	int m_pointLigCreateNum = 0;
	int m_spotLigCreateNum = 0;

	struct LigCameraDatas
	{
		Matrix lightCameraProjectionMatrix;	//���C�g�r���[�v���W�F�N�V�����s��
		Vector3 lightCameraPosition;	//���C�g�J�����̈ʒu
		float pad;
		Vector3 lightCameraDirection;	//���C�g�J�����̌���
	};
	LigCameraDatas m_ligCameraData;
	int m_ligCameraDataSize = sizeof(m_ligCameraData);

	Camera m_lightCamera;	//�V���h�E�}�b�v�p�̃��C�g�̈ʒu�̃J�����B�e�X�g�p

public:

	/// @brief ���C�g�}�l�[�W���[�̃C���X�^���X���쐬
	static void CreateInstance()
	{
		if (!m_instance)
		{
			m_instance = new LightManager;
		}
	}

	/// @brief ���C�g�}�l�[�W���[�̃C���X�^���X���폜
	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}

	/// @brief ���C�g�}�l�[�W���[�̃C���X�^���X���擾����B
	static LightManager* GetInstance() { return m_instance; };
	
	/// @brief ���C�g�̃f�[�^�̉���擾����(�萔�o�b�t�@�ɓn���p)
	/// @return �S���C�g�̃f�[�^
	LigDatas* GetLigDatas() { return &m_ligData; };

	/// @brief ���C�g�̃f�[�^�̉�̃T�C�Y���擾����(�萔�o�b�t�@�ɓn���p)
	/// @return �S���C�g�̃f�[�^�̃T�C�Y
	int GetLigDataSize() { return m_size; };

	/// @brief �J�����̃|�W�V�������X�V����B
	void UpdateEyePos() { m_ligData.eyePos = g_camera3D->GetPosition(); };

	//���C�g�̐���������B
	int GetDirectionLigNum() { return m_ligData.directionLightNum; };
	int GetPointLigNum() { return m_ligData.pointLightNum; };
	int GetSpotLigNum() { return m_ligData.spotLightNum; };

	

	//�e�p//////////////////////////////////////////////////////////////////////////////////////////////////
	
	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̃f�[�^�̉���擾����(�萔�o�b�t�@�ɓn���p)
	/// @return ���C�g�J�����̃f�[�^
	LigCameraDatas* GetLigCameraDatas() { return &m_ligCameraData; };

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̃f�[�^�̉�̃T�C�Y���擾����(�萔�o�b�t�@�ɓn���p)
	/// @return 
	int GetLigCameraDataSize() { return m_ligCameraDataSize; };
	
	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�������擾
	/// @return ���C�g�J����
	Camera* GetLightCamera()
	{
		return &m_lightCamera;
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̍��W���w�肷��B
	/// @param pos ���C�g�J�����̍��W
	void SetLightCameraPosition(const Vector3& pos)
	{
		m_lightCamera.SetPosition(pos);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraPosition = pos;
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();

		m_ligCameraData.lightCameraDirection = m_lightCamera.GetTarget() - m_lightCamera.GetPosition();
		m_ligCameraData.lightCameraDirection.Normalize();
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̃^�[�Q�b�g�̍��W���w�肷��B
	/// @param targetPos ���C�g�J�����̃^�[�Q�b�g�̍��W
	void SetLightCameraTarget(const Vector3& targetPos)
	{
		m_lightCamera.SetTarget(targetPos);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();

		m_ligCameraData.lightCameraDirection = m_lightCamera.GetTarget() - m_lightCamera.GetPosition();
		m_ligCameraData.lightCameraDirection.Normalize();
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̏�������w�肷��B
	/// @param up �J�����̏�����̃x�N�g��
	void SetLightCameraUp(const Vector3& up)
	{
		m_lightCamera.SetUp(up);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̎ˉe�s��̍X�V���@��ݒ肷��B
	/// @param func �ˉe�s��̍X�V���@
	void SetLightCameraUpdateProjectionMatixFunc(Camera::EnUpdateProjMatrixFunc func)
	{
		m_lightCamera.SetUpdateProjMatrixFunc(func);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̉������w�肷��(���s���e����)
	/// @param width ���C�g�J�����̉���
	void SetLightCameraWidth(const float& width)
	{
		m_lightCamera.SetWidth(width);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̍������w�肷��(���s���e����)
	/// @param height ���C�g�J�����̍���
	void SetLightCameraHeight(const float& height)
	{
		m_lightCamera.SetWidth(height);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}
};

