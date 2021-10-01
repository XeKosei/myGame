#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"

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
		PointLigData pointLight[POINTLIGHT_NUMBER_MAX];		//�|�C���g���C�g�̃f�[�^�̔z��
		SpotLigData spotLight[SPOTLIGHT_NUMBER_MAX];			//�X�|�b�g���C�g�̃f�[�^�̔z��
		Vector3 eyePos;					//�J�����̈ʒu
		int createdDirLigTotal = 0;		//�f�B���N�V�������C�g�����ꂽ����
		int createdPointLigTotal = 0;	//�|�C���g���C�g�����ꂽ����
		int createdSpotLigTotal = 0;	//�X�|�b�g���C�g�����ꂽ����
	};
	LigDatas m_ligData;					//���C�g�̃f�[�^
	int m_size = sizeof(m_ligData);		//���C�g�̃f�[�^�̃T�C�Y

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

	LigCameraDatas m_spotLigCameraData;
	int m_spotLigCameraDataSize = sizeof(m_spotLigCameraData);
	Camera m_spotLightCamera;	//�X�|�b�g���C�g�̌���`�悷��p�̃X�|�b�g���C�g�̈ʒu�̃J����

	//���C�g�̔ԍ����Ǘ�����|�C���^
	int* m_dirLigNum[DIRECTIONLIGHT_NUMBER_MAX] = { nullptr,nullptr, nullptr, nullptr, nullptr };
	int* m_pointLigNum[POINTLIGHT_NUMBER_MAX] = {
		nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr,
		nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr
	};
	int* m_spotLigNum[SPOTLIGHT_NUMBER_MAX] = {
		nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr,
		nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr
	};


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

	//�V��������郉�C�g�ɔԍ���^���邽�߂̊֐��B
	//�^������ԍ������ɍ���郉�C�g�ɗ^����ԍ��ɂ���B
	int GetNewDirLigNum() { return m_ligData.createdDirLigTotal++; };
	int GetNewPointLigNum() { return m_ligData.createdPointLigTotal++; };
	int GetNewSpotLigNum() { return m_ligData.createdSpotLigTotal++; };

	/// @brief ���C�g�̔ԍ��ɎQ�Ƃł���悤�ɁA�A�h���X���i�[���鏈���B
	/// @param num 
	void SetDirLigNum(int* num) { m_dirLigNum[*num] = num; };
	void SetPointLigNum(int* num) { m_pointLigNum[*num] = num; };
	void SetSpotLigNum(int* num) { m_spotLigNum[*num] = num; };

	//�f�B���N�V�������C�g�p/////////////////////////////////////////////////////////////////////////////////

	/// @brief �V�����f�B���N�V�������C�g�����ꂽ�ۂ̏���
	/// @param newDirLig �V�������ꂽ�f�B���N�V�������C�g
	void AddNewDirectionLight(DirLigData* newDirLigData)
	{
		//���C�g�̐����ŏ��Ɍ��߂����ȏ�Ȃ�throw����(�����ς����Ƃӂ��ɋN����)
		if (m_ligData.createdDirLigTotal >= DIRECTIONLIGHT_NUMBER_MAX)
		{
			MessageBoxA(nullptr, "�f�B���N�V�������C�g�̐����ő吔�𒴂��Ă��܂��B\n", "�G���[", MB_OK);
		}

		//�V�������ꂽ�f�B���N�V�������C�g�̃f�[�^��z��̋󂫂̐擪�Ɋi�[����B
		m_ligData.directionLight[m_ligData.createdDirLigTotal] = *newDirLigData;
	}

	/// @brief �f�B���N�V�������C�g�̏����X�V����B
	/// @param dirLigNum �X�V���������C�g�̔ԍ�
	/// @param dirLigData �X�V���������C�g�̐V�������C�g�f�[�^
	void UpdateDirectionLight(int dirLigNum, DirLigData* dirLigData)
	{
		m_ligData.directionLight[dirLigNum] = *dirLigData;
	}

	/// @brief ���C�g���폜���鎞�ɍs������
	/// @param num �폜���郉�C�g�̔ԍ�
	void RemoveDirectionLight(int num)
	{
		DirectionLightNumMinus();

		//���C�g�̔z����A�������C�g�̈ʒu�������l�߂Ă����B
		for (int i = num; i < m_ligData.createdDirLigTotal - 1; i++)
		{
			m_ligData.directionLight[i] = m_ligData.directionLight[i + 1];

			//���C�g�̔ԍ�������l�߂Ă����B
			*m_dirLigNum[num + 1]--;
			m_dirLigNum[num + 1] = nullptr;
		}
	}

	/// @brief ���C�g���폜���ꂽ�Ƃ��A���ꂽ���C�g�̐������炷���߂̊֐�
	void DirectionLightNumMinus()
	{
		m_ligData.createdDirLigTotal--;
		//���C�g�̐���0�ȉ��ɂȂ鎞�͂��������Ȃ��Ă���̂�throw����(�N���蓾�Ȃ��ƐM������)
		if (m_ligData.createdDirLigTotal < 0)
		{
			MessageBoxA(nullptr, "�f�B���N�V�������C�g�̐����}�C�i�X�ɂȂ��Ă��܂��B\n", "�G���[", MB_OK);
		}
	}

	//�|�C���g���C�g�p/////////////////////////////////////////////////////////////////////////////////

	/// @brief �V�����|�C���g���C�g�����ꂽ�ۂ̏���
	/// @param newDirLig �V�������ꂽ�f�B���N�V�������C�g
	void AddNewPointLight(PointLigData* newPointLigData)
	{
		//���C�g�̐����ŏ��Ɍ��߂����ȏ�Ȃ�throw����(�����ς����Ƃӂ��ɋN����)
		if (m_ligData.createdPointLigTotal >= POINTLIGHT_NUMBER_MAX)
		{
			MessageBoxA(nullptr, "�|�C���g���C�g�̐����ő吔�𒴂��Ă��܂��B\n", "�G���[", MB_OK);
		}

		//�V�������ꂽ�|�C���g���C�g�̃f�[�^��z��̋󂫂̐擪�Ɋi�[����B
		m_ligData.pointLight[m_ligData.createdPointLigTotal] = *newPointLigData;
	}

	/// @brief �|�C���g���C�g�̏����X�V����B
	/// @param dirLigNum �X�V���������C�g�̔ԍ�
	/// @param dirLigData �X�V���������C�g�̐V�������C�g�f�[�^
	void UpdatePointLight(int pointLigNum, PointLigData* pointLigData)
	{
		m_ligData.pointLight[pointLigNum] = *pointLigData;
	}

	/// @brief ���C�g���폜���鎞�ɍs������
	/// @param num �폜���郉�C�g�̔ԍ�
	void RemovePointLight(int num)
	{
		PointLightNumMinus();

		//���C�g�̔z����A�������C�g�̈ʒu�������l�߂Ă����B
		for (int i = num; i < m_ligData.createdPointLigTotal - 1; i++)
		{
			m_ligData.pointLight[i] = m_ligData.pointLight[i + 1];

			//���C�g�̔ԍ�������l�߂Ă����B
			*m_pointLigNum[num + 1]--;
			m_pointLigNum[num + 1] = nullptr;
		}
	}

	/// @brief ���C�g���폜���ꂽ�Ƃ��A���ꂽ���C�g�̐������炷���߂̊֐�
	void PointLightNumMinus()
	{
		m_ligData.createdPointLigTotal--;
		//���C�g�̐���0�ȉ��ɂȂ鎞�͂��������Ȃ��Ă���̂�throw����(�N���蓾�Ȃ��ƐM������)
		if (m_ligData.createdPointLigTotal < 0)
		{
			MessageBoxA(nullptr, "�|�C���g���C�g�̐����}�C�i�X�ɂȂ��Ă��܂��B\n", "�G���[", MB_OK);
		}
	}

	//�X�|�b�g���C�g�p/////////////////////////////////////////////////////////////////////////////////

	/// @brief �V�����X�|�b�g���C�����ꂽ�ۂ̏���
	/// @param newDirLig �V�������ꂽ�f�B���N�V�������C�g
	void AddNewSpotLight(SpotLigData* newSpotLigData)
	{
		//���C�g�̐����ŏ��Ɍ��߂����ȏ�Ȃ�throw����(�����ς����Ƃӂ��ɋN����)
		if (m_ligData.createdSpotLigTotal >= SPOTLIGHT_NUMBER_MAX)
		{
			MessageBoxA(nullptr, "�X�|�b�g���C�g�̐����ő吔�𒴂��Ă��܂��B\n", "�G���[", MB_OK);
		}

		//�V�������ꂽ�|�C���g���C�g�̃f�[�^��z��̋󂫂̐擪�Ɋi�[����B
		m_ligData.spotLight[m_ligData.createdSpotLigTotal] = *newSpotLigData;
	}

	/// @brief �X�|�b�g���C�g�̏����X�V����B
	/// @param dirLigNum �X�V���������C�g�̔ԍ�
	/// @param dirLigData �X�V���������C�g�̐V�������C�g�f�[�^
	void UpdateSpotLight(int spotLigNum, SpotLigData* spotLigData)
	{
		m_ligData.spotLight[spotLigNum] = *spotLigData;
	}

	/// @brief ���C�g���폜���鎞�ɍs������
	/// @param num �폜���郉�C�g�̔ԍ�
	void RemoveSpotLight(int num)
	{
		SpotLightNumMinus();

		//���C�g�̔z����A�������C�g�̈ʒu�������l�߂Ă����B
		for (int i = num; i < m_ligData.createdSpotLigTotal - 1; i++)
		{
			m_ligData.spotLight[i] = m_ligData.spotLight[i + 1];

			//���C�g�̔ԍ�������l�߂Ă����B
			*m_spotLigNum[num + 1]--;
			m_spotLigNum[num + 1] = nullptr;
		}
	}

	/// @brief ���C�g���폜���ꂽ�Ƃ��A���ꂽ���C�g�̐������炷���߂̊֐�
	void SpotLightNumMinus()
	{
		m_ligData.createdSpotLigTotal--;
		//���C�g�̐���0�ȉ��ɂȂ鎞�͂��������Ȃ��Ă���̂�throw����(�N���蓾�Ȃ��ƐM������)
		if (m_ligData.createdSpotLigTotal < 0)
		{
			MessageBoxA(nullptr, "�X�|�b�g���C�g�̐����}�C�i�X�ɂȂ��Ă��܂��B\n", "�G���[", MB_OK);
		}
	}

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
	void SetLightCameraUpdateProjMatrixFunc(Camera::EnUpdateProjMatrixFunc func)
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
		m_lightCamera.SetHeight(height);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	//�X�|�b�g���C�g�̃J�����p//////////////////////////////////////////////////////////////////////////////////////////////////

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̃f�[�^�̉���擾����(�萔�o�b�t�@�ɓn���p)
	/// @return ���C�g�J�����̃f�[�^
	LigCameraDatas* GetSpotLigCameraDatas() { return &m_spotLigCameraData; };

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̃f�[�^�̉�̃T�C�Y���擾����(�萔�o�b�t�@�ɓn���p)
	/// @return 
	int GetSpotLigCameraDataSize() { return m_spotLigCameraDataSize; };

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�������擾
	/// @return ���C�g�J����
	Camera* GetSpotLightCamera()
	{
		return &m_spotLightCamera;
	}

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̍��W���w�肷��B
	/// @param pos ���C�g�J�����̍��W
	void SetSpotLightCameraPosition(const Vector3& pos)
	{
		m_spotLightCamera.SetPosition(pos);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraPosition = pos;
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();

		m_spotLigCameraData.lightCameraDirection = m_spotLightCamera.GetTarget() - m_spotLightCamera.GetPosition();
		m_spotLigCameraData.lightCameraDirection.Normalize();
	}

	/// @brief�X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̃^�[�Q�b�g�̍��W���w�肷��B
	/// @param targetPos ���C�g�J�����̃^�[�Q�b�g�̍��W
	void SetSpotLightCameraTarget(const Vector3& targetPos)
	{
		m_spotLightCamera.SetTarget(targetPos);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();

		m_spotLigCameraData.lightCameraDirection = m_spotLightCamera.GetTarget() - m_spotLightCamera.GetPosition();
		m_spotLigCameraData.lightCameraDirection.Normalize();
	}

	void SetSpotLightCameraAngle(const float angle)
	{

		m_spotLightCamera.SetViewAngle(angle);

		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̏�������w�肷��B
	/// @param up �J�����̏�����̃x�N�g��
	void SetSpotLightCameraUp(const Vector3& up)
	{
		m_spotLightCamera.SetUp(up);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̎ˉe�s��̍X�V���@��ݒ肷��B
	/// @param func �ˉe�s��̍X�V���@
	void SetSpotLightCameraUpdateProjMatrixFunc(Camera::EnUpdateProjMatrixFunc func)
	{
		m_spotLightCamera.SetUpdateProjMatrixFunc(func);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief �X�|�b�g���C�g�Ɏg�p���郉�C�g�J�����̉������w�肷��(���s���e����)
	/// @param width ���C�g�J�����̉���
	void SetSpotLightCameraWidth(const float& width)
	{
		m_spotLightCamera.SetWidth(width);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief �e�̕`��Ɏg�p���郉�C�g�J�����̍������w�肷��(���s���e����)
	/// @param height ���C�g�J�����̍���
	void SetSpotLightCameraHeight(const float& height)
	{
		m_spotLightCamera.SetHeight(height);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

};