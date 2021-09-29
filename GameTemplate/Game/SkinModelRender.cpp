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
	//モデルの初期化データ
	ModelInitData modelInitData;
	//影の初期化データ
	ModelInitData shadowModelInitData;
	//スポットライト用のモデルの初期化データ
	ModelInitData spotLightModelInitData;

	//モデルのファイルパスを指定
	modelInitData.m_tkmFilePath = modelPath;
	shadowModelInitData.m_tkmFilePath = modelPath;
	spotLightModelInitData.m_tkmFilePath = modelPath;

	//シェーダーパスの指定
	modelInitData.m_fxFilePath = "Assets/shader/shadowReceiver.fx";
	shadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
	spotLightModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";

	//シェーダーの頂点シェーダーのエントリー関数名の指定
	modelInitData.m_vsEntryPointFunc = "VSMain";
	shadowModelInitData.m_vsEntryPointFunc = "VSMain";
	spotLightModelInitData.m_vsEntryPointFunc = "VSMain";

	//シェーダーのピクセルシェーダーのエントリー関数名の指定
	modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	spotLightModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

	//スケルトンが存在しているときはスケルトンを初期化
	if (skeletonPath != nullptr)
	{
		m_skeleton.Init(skeletonPath);
		modelInitData.m_skeleton = &m_skeleton;
		shadowModelInitData.m_skeleton = &m_skeleton;
		spotLightModelInitData.m_skeleton = &m_skeleton;
	}

	//カラーバッファのフォーマットを指定。
	modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32_FLOAT;
	spotLightModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32_FLOAT;

	//モデルデータの上方向の軸を指定
	modelInitData.m_modelUpAxis = enModelUpAxisZ;
	shadowModelInitData.m_modelUpAxis = enModelUpAxisZ;
	spotLightModelInitData.m_modelUpAxis = enModelUpAxisZ;

	//モデルの影を落とすために影のテクスチャを紐づける。
	modelInitData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetBlurShadowMap();
	modelInitData.m_expandShaderResoruceView[1] = &PostEffectManager::GetInstance()->GetSpotLightMap();

	//定数バッファをモデルに紐づける
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

	//モデルの初期化
	m_model[eModel].Init(modelInitData);

	//影描画モデルの初期化
	m_model[eModel_Shadow].Init(shadowModelInitData);
	//スポットライト用のモデルの初期化
	m_model[eModel_SpotLight].Init(spotLightModelInitData);

	//アニメーション関連の初期化
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
	//レンダーコンテキストの描画先で分岐
	switch (rc.GetRenderStep()) {
	case RenderContext::eStep_Render:
		//画面に描画
		m_model[eModel].Draw(rc, camera);
		break;
	case RenderContext::eStep_RenderShadowMap:
		//影を作るモデルの時だけ影を描画
		if (m_isShadowCaster)
		{
			m_model[eModel_Shadow].Draw(rc, camera);
		}
		break;
	case RenderContext::eStep_RenderSpotLightMap:
		//スポットライト用
		m_model[eModel_SpotLight].Draw(rc, camera);
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
}

void SkinModelRender::PreLoadModel(const char* tkmFilePath)
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