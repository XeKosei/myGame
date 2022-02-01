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
		//モデルの初期化データ
		ModelInitData modelInitData;
		//影の初期化データ
		//ModelInitData shadowModelInitData;
		//スポットライト用のモデルの初期化データ
		ModelInitData spotLightModelInitData[3];

		//モデルのファイルパスを指定
		modelInitData.m_tkmFilePath = modelPath;
		//shadowModelInitData.m_tkmFilePath = modelPath;
		spotLightModelInitData[0].m_tkmFilePath = modelPath;
		spotLightModelInitData[1].m_tkmFilePath = modelPath;
		spotLightModelInitData[2].m_tkmFilePath = modelPath;

		//シェーダーパスの指定
		modelInitData.m_fxFilePath = "Assets/shader/PBR.fx";
		//shadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
		spotLightModelInitData[0].m_fxFilePath = "Assets/shader/GetDepth.fx";
		spotLightModelInitData[1].m_fxFilePath = "Assets/shader/GetDepth.fx";
		spotLightModelInitData[2].m_fxFilePath = "Assets/shader/GetDepth.fx";

		//シェーダーの頂点シェーダーのエントリー関数名の指定
		modelInitData.m_vsEntryPointFunc = "VSMain";
		//shadowModelInitData.m_vsEntryPointFunc = "VSMain";
		spotLightModelInitData[0].m_vsEntryPointFunc = "VSMain";
		spotLightModelInitData[1].m_vsEntryPointFunc = "VSMain";
		spotLightModelInitData[2].m_vsEntryPointFunc = "VSMain";

		//シェーダーのピクセルシェーダーのエントリー関数名の指定
		modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		//shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		spotLightModelInitData[0].m_vsSkinEntryPointFunc = "VSSkinMain";
		spotLightModelInitData[1].m_vsSkinEntryPointFunc = "VSSkinMain";
		spotLightModelInitData[2].m_vsSkinEntryPointFunc = "VSSkinMain";

		//スケルトンが存在しているときはスケルトンを初期化
		if (skeletonPath != nullptr)
		{
			m_skeleton.Init(skeletonPath);
			modelInitData.m_skeleton = &m_skeleton;
			//shadowModelInitData.m_skeleton = &m_skeleton;
			spotLightModelInitData[0].m_skeleton = &m_skeleton;
			spotLightModelInitData[1].m_skeleton = &m_skeleton;
			spotLightModelInitData[2].m_skeleton = &m_skeleton;
		}

		//カラーバッファのフォーマットを指定。
		modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//shadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32_FLOAT;
		spotLightModelInitData[0].m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		spotLightModelInitData[1].m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		spotLightModelInitData[2].m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//モデルデータの上方向の軸を指定
		modelInitData.m_modelUpAxis = enModelUpAxisZ;
		//shadowModelInitData.m_modelUpAxis = enModelUpAxisZ;
		spotLightModelInitData[0].m_modelUpAxis = enModelUpAxisZ;
		spotLightModelInitData[1].m_modelUpAxis = enModelUpAxisZ;
		spotLightModelInitData[2].m_modelUpAxis = enModelUpAxisZ;

		//モデルの影を落とすために影のテクスチャを紐づける。
		//modelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetBlurShadowMap();
		modelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetClairvoyanceMap();
		modelInitData.m_expandShaderResoruceView[1] = &PostEffectManager::GetInstance()->GetSpotLightMap(0);
		modelInitData.m_expandShaderResoruceView[2] = &PostEffectManager::GetInstance()->GetSpotLightMap(1);
		modelInitData.m_expandShaderResoruceView[3] = &PostEffectManager::GetInstance()->GetSpotLightMap(2);

		//定数バッファをモデルに紐づける
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

		//モデルの初期化
		m_model[eModel].Init(modelInitData);
		//影描画モデルの初期化
		//m_model[eModel_Shadow].Init(shadowModelInitData);
		//スポットライト用のモデルの初期化
		m_model[eModel_SpotLight00].Init(spotLightModelInitData[0]);
		m_model[eModel_SpotLight01].Init(spotLightModelInitData[1]);
		m_model[eModel_SpotLight02].Init(spotLightModelInitData[2]);

		//アニメーション関連の初期化
		m_animationClips = animClips;
		m_animationClipNum = animClipNum;

		if (m_animationClips != nullptr)
		{
			m_animation.Init(m_skeleton, m_animationClips, m_animationClipNum);
		}

		//拡張するならば
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
		//レンダーコンテキストの描画先で分岐
		switch (rc.GetRenderStep()) {
		case RenderContext::eStep_Render:
			//画面に描画
			if (m_isNormalCaster)
			{
				m_model[eModel].Draw(rc, camera);
			}
			break;
		//case RenderContext::eStep_RenderShadowMap:
		//	//影を作るモデルの時だけ影を描画
		//	if (m_isShadowCaster)
		//	{
		//		m_model[eModel_Shadow].Draw(rc, camera);
		//	}
		//	break;
		case RenderContext::eStep_RenderSpotLightMap00:
			//スポットライト用
			if (m_isSpotLightCaster)
			{
				m_model[eModel_SpotLight00].Draw(rc, camera);
			}
			break;
		case RenderContext::eStep_RenderSpotLightMap01:
			//スポットライト用
			if (m_isSpotLightCaster)
			{
				m_model[eModel_SpotLight01].Draw(rc, camera);
			}
			break;
		case RenderContext::eStep_RenderSpotLightMap02:
			//スポットライト用
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
		//モデルをアップデート
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
		//2画面用にCSkinModelRenderはModelクラスを2つ保持しているが、どちらもカメラ以外同じなので0番目のモデルで判定する。
		return m_model[eModel].isLineHitModel(start, end, crossPoint);
	}

	void SkinModelRender::PreLoadModel(const char* tkmFilePath)
	{
		//プリロードはまだできない
		TkmFile* tkmFile = ResourceBankManager::GetInstance()->GetTkmFileFromBank(tkmFilePath);

		if (tkmFile == nullptr)
		{
			//未登録
			tkmFile = new TkmFile;
			tkmFile->Load(tkmFilePath);
			ResourceBankManager::GetInstance()->RegistTkmFileToBank(tkmFilePath, tkmFile);
		}
	}
}