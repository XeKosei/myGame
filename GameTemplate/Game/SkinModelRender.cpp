#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::~SkinModelRender()
{

}
void SkinModelRender::Update()
{

}

void SkinModelRender::Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum)
{
	//���f���̏������f�[�^
	ModelInitData modelInitData;
	//�e�̏������f�[�^
	ModelInitData shadowModelInitData;
	//�X�|�b�g���C�g�p�̃��f���̏������f�[�^
	ModelInitData spotLightModelInitData;

	//���f���̃t�@�C���p�X���w��
	modelInitData.m_tkmFilePath = modelPath;
	shadowModelInitData.m_tkmFilePath = modelPath;
	spotLightModelInitData.m_tkmFilePath = modelPath;

	//�V�F�[�_�[�p�X�̎w��
	modelInitData.m_fxFilePath = "Assets/shader/shadowReceiver.fx";
	shadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
	spotLightModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";

	//�V�F�[�_�[�̒��_�V�F�[�_�[�̃G���g���[�֐����̎w��
	modelInitData.m_vsEntryPointFunc = "VSMain";
	shadowModelInitData.m_vsEntryPointFunc = "VSMain";
	spotLightModelInitData.m_vsEntryPointFunc = "VSMain";

	//�V�F�[�_�[�̃s�N�Z���V�F�[�_�[�̃G���g���[�֐����̎w��
	modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	spotLightModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

	//�X�P���g�������݂��Ă���Ƃ��̓X�P���g����������
	if (skeletonPath != nullptr)
	{
		m_skeleton.Init(skeletonPath);
		modelInitData.m_skeleton = &m_skeleton;
		shadowModelInitData.m_skeleton = &m_skeleton;
		spotLightModelInitData.m_skeleton = &m_skeleton;
	}

	//�J���[�o�b�t�@�̃t�H�[�}�b�g���w��B
	modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32_FLOAT;
	spotLightModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32_FLOAT;

	//���f���f�[�^�̏�����̎����w��
	modelInitData.m_modelUpAxis = enModelUpAxisZ;
	shadowModelInitData.m_modelUpAxis = enModelUpAxisZ;
	spotLightModelInitData.m_modelUpAxis = enModelUpAxisZ;

	//���f���̉e�𗎂Ƃ����߂ɉe�̃e�N�X�`����R�Â���B
	modelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetBlurShadowMap();
	modelInitData.m_expandShaderResoruceView[1] = &PostEffectManager::GetInstance()->GetSpotLightMap();

	//�萔�o�b�t�@�����f���ɕR�Â���
	modelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigDataSize();
	modelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigDatas();
	modelInitData.m_expandConstantBufferSize[1] = LightManager::GetInstance()->GetLigCameraDataSize();
	modelInitData.m_expandConstantBuffer[1] = LightManager::GetInstance()->GetLigCameraDatas();
	modelInitData.m_expandConstantBufferSize[2] = LightManager::GetInstance()->GetSpotLigCameraDataSize();
	modelInitData.m_expandConstantBuffer[2] = LightManager::GetInstance()->GetSpotLigCameraDatas();

	shadowModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigCameraDataSize();
	shadowModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigCameraDatas();
	spotLightModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetSpotLigCameraDataSize();
	spotLightModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetSpotLigCameraDatas();

	//���f���̏�����
	m_model[eModel].Init(modelInitData);

	//�e�`�惂�f���̏�����
	m_model[eModel_Shadow].Init(shadowModelInitData);
	//�X�|�b�g���C�g�p�̃��f���̏�����
	m_model[eModel_SpotLight].Init(spotLightModelInitData);

	//�A�j���[�V�����֘A�̏�����
	m_animationClips = animClips;
	m_animationClipNum = animClipNum;

	if (m_animationClips != nullptr)
	{
		m_animation.Init(m_skeleton, m_animationClips, m_animationClipNum);
	}
}

void SkinModelRender::Init(const char* modelPath, const char* skeletonPath)
{
	Init(modelPath, skeletonPath, nullptr, 0);
}

void SkinModelRender::Init(const char* modelPath)
{
	Init(modelPath, nullptr, nullptr, 0);
}

Matrix SkinModelRender::GetWorldMatrixFromBoneName(const wchar_t* boneName)
{
	int boneNo = m_skeleton.FindBoneID(boneName);
	return m_skeleton.GetBone(boneNo)->GetWorldMatrix();
}


void SkinModelRender::Render(RenderContext& rc, Camera* camera)
{
	//�����_�[�R���e�L�X�g�̕`���ŕ���
	switch (rc.GetRenderStep()) {
	case RenderContext::eStep_Render:
		//��ʂɕ`��
		m_model[eModel].Draw(rc, camera);
		break;
	case RenderContext::eStep_RenderShadowMap:
		//�e����郂�f���̎������e��`��
		if (m_isShadowCaster)
		{
			m_model[eModel_Shadow].Draw(rc, camera);
		}
		break;
	case RenderContext::eStep_RenderSpotLightMap:
		//�X�|�b�g���C�g�p
		m_model[eModel_SpotLight].Draw(rc, camera);
		break;
	}
}

void SkinModelRender::UpdateModel()
{
	//���f�����A�b�v�f�[�g
	for (auto& model : m_model)
	{
		model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		m_skeleton.Update(model.GetWorldMatrix());
	}
}

void SkinModelRender::PreLoadModel(const char* tkmFilePath)
{
	//�v�����[�h�͂܂��ł��Ȃ��B

	/*TkmFile* tkmFile = ResourceBankManager::GetInstance()->GetTkmFileFromBank(tkmFilePath);

	if (tkmFile == nullptr)
	{
		//���o�^
		tkmFile = new TkmFile;
		tkmFile->Load(tkmFilePath);
		ResourceBankManager::GetInstance()->RegistTkmFileToBank(tkmFilePath, tkmFile);

	}*/
}