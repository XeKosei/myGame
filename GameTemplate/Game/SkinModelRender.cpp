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
}

void SkinModelRender::Init(const char* modelPath, const char skeletonPath)
{

}

void SkinModelRender::Init(const char* modelPath)
{

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