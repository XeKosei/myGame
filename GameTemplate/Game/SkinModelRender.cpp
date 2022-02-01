#include "stdafx.h"
#include "SkinModelRender.h"
namespace nsHikageri
{
	SkinModelRender::~SkinModelRender()
	{
		if (m_skinModelRenderEX != nullptr)
			DeleteGO(m_skinModelRenderEX);
	}
	void SkinModelRender::Update()
	{

	}

	void SkinModelRender::Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum)
	{
		//���f���̏������f�[�^
		ModelInitData modelInitData;
		//�e�̏������f�[�^
		//ModelInitData shadowModelInitData;
		//�X�|�b�g���C�g�p�̃��f���̏������f�[�^
		ModelInitData spotLightModelInitData[3];

		//���f���̃t�@�C���p�X���w��
		modelInitData.m_tkmFilePath = modelPath;
		//shadowModelInitData.m_tkmFilePath = modelPath;
		spotLightModelInitData[0].m_tkmFilePath = modelPath;
		spotLightModelInitData[1].m_tkmFilePath = modelPath;
		spotLightModelInitData[2].m_tkmFilePath = modelPath;

		//�V�F�[�_�[�p�X�̎w��
		modelInitData.m_fxFilePath = "Assets/shader/PBR.fx";
		//shadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
		spotLightModelInitData[0].m_fxFilePath = "Assets/shader/GetDepth.fx";
		spotLightModelInitData[1].m_fxFilePath = "Assets/shader/GetDepth.fx";
		spotLightModelInitData[2].m_fxFilePath = "Assets/shader/GetDepth.fx";

		//�V�F�[�_�[�̒��_�V�F�[�_�[�̃G���g���[�֐����̎w��
		modelInitData.m_vsEntryPointFunc = "VSMain";
		//shadowModelInitData.m_vsEntryPointFunc = "VSMain";
		spotLightModelInitData[0].m_vsEntryPointFunc = "VSMain";
		spotLightModelInitData[1].m_vsEntryPointFunc = "VSMain";
		spotLightModelInitData[2].m_vsEntryPointFunc = "VSMain";

		//�V�F�[�_�[�̃s�N�Z���V�F�[�_�[�̃G���g���[�֐����̎w��
		modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		//shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		spotLightModelInitData[0].m_vsSkinEntryPointFunc = "VSSkinMain";
		spotLightModelInitData[1].m_vsSkinEntryPointFunc = "VSSkinMain";
		spotLightModelInitData[2].m_vsSkinEntryPointFunc = "VSSkinMain";

		//�X�P���g�������݂��Ă���Ƃ��̓X�P���g����������
		if (skeletonPath != nullptr)
		{
			m_skeleton.Init(skeletonPath);
			modelInitData.m_skeleton = &m_skeleton;
			//shadowModelInitData.m_skeleton = &m_skeleton;
			spotLightModelInitData[0].m_skeleton = &m_skeleton;
			spotLightModelInitData[1].m_skeleton = &m_skeleton;
			spotLightModelInitData[2].m_skeleton = &m_skeleton;
		}

		//�J���[�o�b�t�@�̃t�H�[�}�b�g���w��B
		modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//shadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32_FLOAT;
		spotLightModelInitData[0].m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		spotLightModelInitData[1].m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		spotLightModelInitData[2].m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//���f���f�[�^�̏�����̎����w��
		modelInitData.m_modelUpAxis = enModelUpAxisZ;
		//shadowModelInitData.m_modelUpAxis = enModelUpAxisZ;
		spotLightModelInitData[0].m_modelUpAxis = enModelUpAxisZ;
		spotLightModelInitData[1].m_modelUpAxis = enModelUpAxisZ;
		spotLightModelInitData[2].m_modelUpAxis = enModelUpAxisZ;

		//���f���̉e�𗎂Ƃ����߂ɉe�̃e�N�X�`����R�Â���B
		//modelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetBlurShadowMap();
		modelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetClairvoyanceMap();
		modelInitData.m_expandShaderResoruceView[1] = &PostEffectManager::GetInstance()->GetSpotLightMap(0);
		modelInitData.m_expandShaderResoruceView[2] = &PostEffectManager::GetInstance()->GetSpotLightMap(1);
		modelInitData.m_expandShaderResoruceView[3] = &PostEffectManager::GetInstance()->GetSpotLightMap(2);

		//�萔�o�b�t�@�����f���ɕR�Â���
		modelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigDataSize();
		modelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigDatas();
		//modelInitData.m_expandConstantBufferSize[1] = LightManager::GetInstance()->GetLigCameraDataSize();
		//modelInitData.m_expandConstantBuffer[1] = LightManager::GetInstance()->GetLigCameraDatas();
		//modelInitData.m_expandConstantBufferSize[2] = LightManager::GetInstance()->GetSpotLigCameraDataSize();
		//modelInitData.m_expandConstantBuffer[2] = LightManager::GetInstance()->GetSpotLigCameraDatas();

		//shadowModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigCameraDataSize();
		//shadowModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigCameraDatas();
		
		spotLightModelInitData[0].m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetSpotLigCameraDataSize(0);
		spotLightModelInitData[0].m_expandConstantBuffer[0] = LightManager::GetInstance()->GetSpotLigCameraDatas(0);
		spotLightModelInitData[1].m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetSpotLigCameraDataSize(1);
		spotLightModelInitData[1].m_expandConstantBuffer[0] = LightManager::GetInstance()->GetSpotLigCameraDatas(1);
		spotLightModelInitData[2].m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetSpotLigCameraDataSize(2);
		spotLightModelInitData[2].m_expandConstantBuffer[0] = LightManager::GetInstance()->GetSpotLigCameraDatas(2);

		//���f���̏�����
		m_model[eModel].Init(modelInitData);
		//�e�`�惂�f���̏�����
		//m_model[eModel_Shadow].Init(shadowModelInitData);
		//�X�|�b�g���C�g�p�̃��f���̏�����
		m_model[eModel_SpotLight00].Init(spotLightModelInitData[0]);
		m_model[eModel_SpotLight01].Init(spotLightModelInitData[1]);
		m_model[eModel_SpotLight02].Init(spotLightModelInitData[2]);

		//�A�j���[�V�����֘A�̏�����
		m_animationClips = animClips;
		m_animationClipNum = animClipNum;

		if (m_animationClips != nullptr)
		{
			m_animation.Init(m_skeleton, m_animationClips, m_animationClipNum);
		}

		//�g������Ȃ��
		if (m_makeSkinModelRenderEX)
		{
			m_skinModelRenderEX = NewGO<SkinModelRenderEX>(0);
			m_skinModelRenderEX->Init(modelPath, skeletonPath, animClips, animClipNum);
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

	Vector3 SkinModelRender::GetWorldPosFromBoneName(const wchar_t* boneName)
	{
		int boneNo = m_skeleton.FindBoneID(boneName);
		m_skeleton.GetBone(boneNo)->CalcWorldTRS(m_position, m_qRot, m_scale);
		return m_skeleton.GetBone(boneNo)->GetBoneWorldPos();
	}

	void SkinModelRender::Render(RenderContext& rc, Camera* camera)
	{
		//�����_�[�R���e�L�X�g�̕`���ŕ���
		switch (rc.GetRenderStep()) {
		case RenderContext::eStep_Render:
			//��ʂɕ`��
			if (m_isNormalCaster)
			{
				m_model[eModel].Draw(rc, camera);
			}
			break;
		//case RenderContext::eStep_RenderShadowMap:
		//	//�e����郂�f���̎������e��`��
		//	if (m_isShadowCaster)
		//	{
		//		m_model[eModel_Shadow].Draw(rc, camera);
		//	}
		//	break;
		case RenderContext::eStep_RenderSpotLightMap00:
			//�X�|�b�g���C�g�p
			if (m_isSpotLightCaster)
			{
				m_model[eModel_SpotLight00].Draw(rc, camera);
			}
			break;
		case RenderContext::eStep_RenderSpotLightMap01:
			//�X�|�b�g���C�g�p
			if (m_isSpotLightCaster)
			{
				m_model[eModel_SpotLight01].Draw(rc, camera);
			}
			break;
		case RenderContext::eStep_RenderSpotLightMap02:
			//�X�|�b�g���C�g�p
			if (m_isSpotLightCaster)
			{
				m_model[eModel_SpotLight02].Draw(rc, camera);
			}
			break;
		case RenderContext::eStep_RenderClairvoyanceMap:
			break;
		default:
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
		if (m_skinModelRenderEX != nullptr)
			m_skinModelRenderEX->UpdateModel();
	}

	bool SkinModelRender::isLineHitModel(const Vector3& start, const Vector3& end, Vector3& crossPoint)
	{
		//2��ʗp��CSkinModelRender��Model�N���X��2�ێ����Ă��邪�A�ǂ�����J�����ȊO�����Ȃ̂�0�Ԗڂ̃��f���Ŕ��肷��B
		return m_model[eModel].isLineHitModel(start, end, crossPoint);
	}

	void SkinModelRender::PreLoadModel(const char* tkmFilePath)
	{
		//�v�����[�h�͂܂��ł��Ȃ�
		TkmFile* tkmFile = ResourceBankManager::GetInstance()->GetTkmFileFromBank(tkmFilePath);

		if (tkmFile == nullptr)
		{
			//���o�^
			tkmFile = new TkmFile;
			tkmFile->Load(tkmFilePath);
			ResourceBankManager::GetInstance()->RegistTkmFileToBank(tkmFilePath, tkmFile);
		}
	}
}