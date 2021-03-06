#include "stdafx.h"
#include "MapChipRender.h"
#include "Level.h"
namespace nsHikageri {
	MapChipRender::MapChipRender()
	{

	}

	MapChipRender::~MapChipRender()
	{
		//作成した分だけ消す。
		DeleteGO(m_modelRender);
	}

	void MapChipRender::Init()
	{

		//スキンモデルレンダラーを作成
		m_modelRender = NewGO<SkinModelRender>(0);
		//ファイルパスを作成。
		char filepath[256];
		sprintf_s(filepath, "Assets/modelData/%s.tkm", m_renderObjectData.name);
		m_modelRender->Init(filepath);

		m_modelRender->SetPosition(m_renderObjectData.position);
		m_modelRender->SetRotation(m_renderObjectData.rotation);
		m_modelRender->SetScale(m_renderObjectData.scale);

		//当たり判定を作成。
		m_physicsStaticObject.CreateFromModel(m_modelRender->GetModel(), m_modelRender->GetModel().GetWorldMatrix());

		//影(予定)

	}
}