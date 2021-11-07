#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h";
#include "Chandelier.h"
#include "Door.h"
namespace nsHikageri
{
	bool GameScene::Start()
	{
		//ステージを作成
		m_backGround = NewGO<nsBackGround::BackGround>(0);

		//プレイヤーを作成
		m_player = NewGO<nsPlayer::Player>(0);
		//エネミーを作成
		m_enemy = NewGO<nsEnemy::Enemy>(0, "enemy");
		m_enemy->SetPlayer(m_player);
		m_enemy->SetMovePos({ -1000.0f,0.0f,-1000.0f }, { -1000.0f,0.0f,1000.0f });

		//ディレクションライトを作成
		/*m_dirLig = NewGO<DirectionLight>(0);
		m_dirLig->SetDirection({ -1.0f, -1.0f, -1.0f });
		m_dirLig->SetColor({ 1.0f,1.0f,1.0f });*/

		Vector3 chandelierPos[5] = {
			{ 1000.0f,800.0f,0.0f } ,
			{ -1000.0f, 800.0f, 1000.0f},
			{-1400.0f, 800.0f, -3600.0f},
			{-1000.0f, 800.0f, 3400.0f},
			{0.0f, 800.0f, -2000.0f}
		};

		//シャンデリア　テスト
		for (int chandelierNum = 0; chandelierNum < 5; chandelierNum++)
		{
			m_chandelier[chandelierNum] = NewGO<nsGimmick::Chandelier>(1);
			m_chandelier[chandelierNum]->SetPlayer(m_player);
			m_chandelier[chandelierNum]->SetEnemy(m_enemy);
			m_chandelier[chandelierNum]->SetPosition(chandelierPos[chandelierNum]);
		}

		//ドア　テスト
		nsGimmick::Door* door = NewGO<nsGimmick::Door>(0);
		door->SetPlayer(m_player);
		door->SetEnemy(m_enemy);
		door->SetDoorColor(nsGimmick::Door::enDoorColor_Red);

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
		if (m_player->GetPlayerMove()->GetPosition().z >= 5000.0f)
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