#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::~SkinModelRender()
{

}
void SkinModelRender::Update()
{

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