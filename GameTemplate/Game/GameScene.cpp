#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h";

namespace nsHikageri
{
	bool GameScene::Start()
	{
		//ステージを作成
		m_backGround = NewGO<nsBackGround::BackGround>(0);

		//プレイヤーを作成
		m_player = NewGO<nsPlayer::Player>(0);

		//エネミーを作成
		for (int i = 0; i < 3; i++)
		{
			m_enemy[i] = NewGO<nsEnemy::Enemy>(0);
			m_enemy[i]->SetPlayer(m_player);
			
		}
		m_enemy[0]->SetMovePos({ -1000.0f,0.0f,-1000.0f }, { -1000.0f,0.0f,1000.0f });
		m_enemy[1]->SetMovePos({ -3400.0f,0.0f,400.0f }, { -3400.0f,0.0f,-1600.0f });
		m_enemy[2]->SetMovePos({ -5000.0f,0.0f,-1200.0f }, { -5000.0f,0.0f,1000.0f });

		//ディレクションライトを作成
		m_dirLig = NewGO<DirectionLight>(0);
		m_dirLig->SetDirection({ -1.0f, -1.0f, -1.0f });
		m_dirLig->SetColor({ 1.0f,1.0f,1.0f });

		//クリアフォント(仮)
		m_clearFont = NewGO<FontRender>(2);
		m_clearFont->SetText(L"GAME CLEAR");
		m_clearFont->SetScale(3.0f);
		m_clearFont->SetPosition({ -320.0f, 50.0f });
		m_clearFont->SetColor({ 0.0f,0.0f,0.0f,0.0f });
		m_clearFont->SetShadowFlag(true);
		m_clearFont->SetShadowOffset(3.0f);
		m_clearFont->SetShadowColor({ 0.0f,0.0f,0.0f,0.0f });

		return true;
	}

	void GameScene::Update()
	{
		GameClear();
	}

	//仮
	void GameScene::GameClear()
	{		
		if (m_player->GetPlayerMove()->GetPosition().z >= 1600.0f)
		{
			if (m_clearFontMoveCount > 0)
			{
				m_clearFontMoveCount--;
			}

			if (m_clearFontMoveCount <= 100 && m_clearFontMoveCount > 0)
			{
				m_clearOverFontColor.r += 0.01f;
				m_clearOverFontColor.g += 0.01f;
				m_clearOverFontColor.b += 0.01f;
				m_clearOverFontColor.a += 0.01f;
				m_clearFont->SetColor(m_clearOverFontColor);
				m_clearOverFontShadowColor.a += 0.01f;
				m_clearFont->SetShadowColor(m_clearOverFontShadowColor);
			}

		}
	}
}