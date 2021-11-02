#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h";
#include "Chandelier.h"

namespace nsHikageri
{
	bool GameScene::Start()
	{
		//�X�e�[�W���쐬
		m_backGround = NewGO<nsBackGround::BackGround>(0);

		//�v���C���[���쐬
		m_player = NewGO<nsPlayer::Player>(0);

		//�G�l�~�[���쐬
		m_enemy = NewGO<nsEnemy::Enemy>(0, "enemy");
		m_enemy->SetPlayer(m_player);
			
		
		m_enemy->SetMovePos({ -1000.0f,0.0f,-1000.0f }, { -1000.0f,0.0f,1000.0f });

		//�f�B���N�V�������C�g���쐬
		m_dirLig = NewGO<DirectionLight>(0);
		m_dirLig->SetDirection({ -1.0f, -1.0f, -1.0f });
		m_dirLig->SetColor({ 1.0f,1.0f,1.0f });

		//�V�����f���A�@�e�X�g
		m_chandelier = NewGO<nsGimmick::Chandelier>(1);
		m_chandelier->SetPlayer(m_player);
		m_chandelier->SetEnemy(m_enemy);

		//�N���A�t�H���g(��)
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

	//��
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