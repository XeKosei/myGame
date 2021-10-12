#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h";

namespace nsHikageri
{
	bool GameScene::Start()
	{
		//ステージを作成
		m_backGround = NewGO<nsBackGround::BackGround>(0);

		//プレイヤーを作成
		m_player = NewGO<nsPlayer::Player>(0);

		//エネミーを作成
		m_enemy = NewGO<nsEnemy::Enemy>(0);

		//ディレクションライトを作成
		m_dirLig = NewGO<DirectionLight>(0);
		m_dirLig->SetDirection({ -1.0f, -1.0f, -1.0f });
		m_dirLig->SetColor({ 1.0f,1.0f,1.0f });

		return true;
	}

	void GameScene::Update()
	{

	}
}