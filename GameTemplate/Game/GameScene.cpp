#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h";

namespace nsHikageri
{
	bool GameScene::Start()
	{
		//�X�e�[�W���쐬
		m_backGround = NewGO<nsBackGround::BackGround>(0);

		//�v���C���[���쐬
		m_player = NewGO<nsPlayer::Player>(0);

		//�G�l�~�[���쐬
		m_enemy = NewGO<nsEnemy::Enemy>(0);

		//�f�B���N�V�������C�g���쐬
		m_dirLig = NewGO<DirectionLight>(0);
		m_dirLig->SetDirection({ -1.0f, -1.0f, -1.0f });
		m_dirLig->SetColor({ 1.0f,1.0f,1.0f });

		return true;
	}

	void GameScene::Update()
	{

	}
}