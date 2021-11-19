#include "stdafx.h"
#include "SkinModelRenderEX.h"
namespace nsHikageri
{
	//スキンモデルレンダーの拡張クラス
	SkinModelRenderEX::~SkinModelRenderEX()
	{

	}
	void SkinModelRenderEX::Update()
	{

	}

	void SkinModelRenderEX::Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum)
	{
		//透視用
		ModelInitData clairvoyanceModelInitData;
		//石化用
		ModelInitData stoneModelInitData;

		clairvoyanceModelInitData.m_tkmFilePath = modelPath;
		stoneModelInitData.m_tkmFilePath = modelPath;

		clairvoyanceModelInitData.m_fxFilePath = "Assets/shader/Clairvoyance.fx";
		stoneModelInitData.m_fxFilePath = "Assets/shader/stoneModel.fx";

		clairvoyanceModelInitData.m_vsEntryPointFunc = "VSMain";
		stoneModelInitData.m_vsEntryPointFunc = "VSMain";

		clairvoyanceModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		stoneModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

		if (skeletonPath != nullptr)
		{
			m_skeleton.Init(skeletonPath);
			clairvoyanceModelInitData.m_skeleton = &m_skeleton;
			stoneModelInitData.m_skeleton = &m_skeleton;
		}
		clairvoyanceModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		stoneModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		clairvoyanceModelInitData.m_modelUpAxis = enModelUpAxisZ;
		stoneModelInitData.m_modelUpAxis = enModelUpAxisZ;;

		clairvoyanceModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetSpotLigCameraDataSize(0);
		clairvoyanceModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetSpotLigCameraDatas(0);

		//stoneModelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetBlurShadowMap();
		stoneModelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetSpotLightMap(0);
		stoneModelInitData.m_expandShaderResoruceView[1] = &PostEffectManager::GetInstance()->GetSpotLightMap(1);
		stoneModelInitData.m_expandShaderResoruceView[2] = &PostEffectManager::GetInstance()->GetSpotLightMap(2);
		
		stoneModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigDataSize();
		stoneModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigDatas();
		//stoneModelInitData.m_expandConstantBufferSize[1] = LightManager::GetInstance()->GetLigCameraDataSize();
		//stoneModelInitData.m_expandConstantBuffer[1] = LightManager::GetInstance()->GetLigCameraDatas();
		//stoneModelInitData.m_expandConstantBufferSize[2] = LightManager::GetInstance()->GetSpotLigCameraDataSize(0);
		//stoneModelInitData.m_expandConstantBuffer[2] = LightManager::GetInstance()->GetSpotLigCameraDatas(0);
		
		m_model[eModelEX_Clairvoyance].Init(clairvoyanceModelInitData);
		m_model[eModelEX_Stone].Init(stoneModelInitData);

		//アニメーション関連の初期化
		m_animationClips = animClips;
		m_animationClipNum = animClipNum;

		if (m_animationClips != nullptr)
		{
			m_animation.Init(m_skeleton, m_animationClips, m_animationClipNum);
		}
	}

	void SkinModelRenderEX::Init(const char* modelPath, const char* skeletonPath)
	{
		Init(modelPath, skeletonPath, nullptr, 0);
	}

	void SkinModelRenderEX::Init(const char* modelPath)
	{
		Init(modelPath, nullptr, nullptr, 0);
	}

	Matrix SkinModelRenderEX::GetWorldMatrixFromBoneName(const wchar_t* boneName)
	{
		int boneNo = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneNo)->GetWorldMatrix();
	}

	Vector3 SkinModelRenderEX::GetWorldPosFromBoneName(const wchar_t* boneName)
	{
		int boneNo = m_skeleton.FindBoneID(boneName);
		m_skeleton.GetBone(boneNo)->CalcWorldTRS(m_position, m_qRot, m_scale);
		return m_skeleton.GetBone(boneNo)->GetBoneWorldPos();
	}

	void SkinModelRenderEX::Render(RenderContext& rc, Camera* camera)
	{
		//レンダーコンテキストの描画先で分岐
		switch (rc.GetRenderStep()) {
		case RenderContext::eStep_Render:
			if (m_stoneRenderFlag)
			{
				m_model[eModelEX_Stone].Draw(rc, camera);
			}
			break;
		case RenderContext::eStep_RenderClairvoyanceMap:
			//透視用
			if (m_isClairvoyanceCaster)
			{
				m_model[eModelEX_Clairvoyance].Draw(rc, camera);
			}
			break;
		default:
			break;
		}
	}

	void SkinModelRenderEX::UpdateModel()
	{
		//モデルをアップデート
		for (auto& model : m_model)
		{
			model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
			m_skeleton.Update(model.GetWorldMatrix());
		}
	}

	void SkinModelRenderEX::PreLoadModel(const char* tkmFilePath)
	{
		//プリロードはまだできない。

		/*TkmFile* tkmFile = ResourceBankManager::GetInstance()->GetTkmFileFromBank(tkmFilePath);

		if (tkmFile == nullptr)
		{
			//未登録
			tkmFile = new TkmFile;
			tkmFile->Load(tkmFilePath);
			ResourceBankManager::GetInstance()->RegistTkmFileToBank(tkmFilePath, tkmFile);

		}*/
	}
}