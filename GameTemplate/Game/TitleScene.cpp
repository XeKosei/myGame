#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace nsHikageri
{
	TitleScene::~TitleScene()
	{
		DeleteGO(m_titleSprite);

	}

	bool TitleScene::Start()
	{
		m_titleSprite = NewGO<SpriteRender>(0);
		m_titleSprite->Init("Assets/Image/Title01.DDS", 1280, 720);

		return true;
	}

	void TitleScene::Update()
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_gameScene = NewGO<nsGameScene::GameScene>(0, "gameScene");
			DeleteGO(this);
		}
	}





}