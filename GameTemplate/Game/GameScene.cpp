#include "stdafx.h"
#include "GameScene.h"
#include "BackGroundInclude.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h";
#include "GimmickInclude.h"
#include "ItemInclude.h"
namespace nsHikageri
{
	bool GameScene::Start()
	{
		//ステージを作成
		m_backGround = NewGO<nsBackGround::BackGround>(0, "backGround");
		m_secretRoom = NewGO<nsBackGround::SecretRoom>(0, "secretRoom");

		//プレイヤーを作成
		m_player = NewGO<nsPlayer::Player>(0);
		//エネミーを作成
		m_enemy = NewGO<nsEnemy::Enemy>(0, "enemy");
		m_enemy->SetPlayer(m_player);

		//ディレクションライトを作成
		/*m_dirLig = NewGO<DirectionLight>(0);
		m_dirLig->SetDirection({ -1.0f, -1.0f, -1.0f });
		m_dirLig->SetColor({ 1.0f,1.0f,1.0f });*/

		////シャンデリア　テスト
		//Vector3 chandelierPos[5] = {
		//	{ 1000.0f,800.0f,0.0f } ,
		//	{ -1000.0f, 800.0f, 1000.0f},
		//	{-1400.0f, 800.0f, -3600.0f},
		//	{-1000.0f, 800.0f, 3400.0f},
		//	{0.0f, 800.0f, -2000.0f}
		//};

		//for (int chandelierNum = 0; chandelierNum < 5; chandelierNum++)
		//{
		//	m_chandelier[chandelierNum] = NewGO<nsGimmick::Chandelier>(1);
		//	m_chandelier[chandelierNum]->SetPlayer(m_player);
		//	m_chandelier[chandelierNum]->SetEnemy(m_enemy);
		//	m_chandelier[chandelierNum]->SetPosition(chandelierPos[chandelierNum]);
		//}

		//ドア　テスト
		//Vector3 doorPos[5]
		//{
		//	{ 0.0f, 0.0f, -100.0f },
		//	{-900.0f, 0.0f, -600.0f},
		//	{-800.0f, 0.0f, -1900.0f},
		//	{-7200.0f,0.0f, 1500.0f},
		//	{-7900.0f, 0.0f, 5400.0f}
		//};

		//Vector3 doorDir[5]
		//{
		//	{1.0f,0.0f,0.0f },
		//	{0.0f, 0.0f, 1.0f},
		//	{-1.0f, 0.0f, 0.0f},
		//	{1.0f,0.0f,0.0f},
		//	{0.0f,0.0f,-1.0f}
		//};

		//for (int doorNum = 0; doorNum < 5; doorNum++)
		//{
		//	m_door[doorNum] = NewGO<nsGimmick::Door>(0);
		//	m_door[doorNum]->SetPlayer(m_player);
		//	m_door[doorNum]->SetEnemy(m_enemy);
		//	m_door[doorNum]->SetPosition(doorPos[doorNum]);
		//	m_door[doorNum]->SetDirection(doorDir[doorNum]);
		//}
		//m_door[0]->SetDoorColor(nsGimmick::Door::enDoorColor_Red);
		//m_door[1]->SetDoorColor(nsGimmick::Door::enDoorColor_Blue);
		//m_door[2]->SetDoorColor(nsGimmick::Door::enDoorColor_Green);
		//m_door[3]->SetDoorColor(nsGimmick::Door::enDoorColor_Yellow);
		//m_door[4]->SetDoorColor(nsGimmick::Door::enDoorColor_Purple);

		////鍵テスト
		//Vector3 KeyPos[5] = {
		//	{1500.0f, 145.0f, 0.0f},
		//	{ -2290.0f, 145.0f, 400.0f },
		//	{110.0f, 145.0f, 2800.0f},
		//	{-11090.0f,145.0f, 2400.0f},
		//	{-7000.0f, 145.0f, -1900.0f}
		//};

		//for (int keyNum = 0; keyNum < 5; keyNum++)
		//{
		//	m_key[keyNum] = NewGO<nsItem::ItemKey>(0);
		//	m_key[keyNum]->SetPlayer(m_player);
		//	m_key[keyNum]->SetPosition(KeyPos[keyNum]);
		//}
		//m_key[0]->SetKeyColor(nsGimmick::Door::enDoorColor_Red);
		//m_key[1]->SetKeyColor(nsGimmick::Door::enDoorColor_Blue);
		//m_key[2]->SetKeyColor(nsGimmick::Door::enDoorColor_Green);
		//m_key[3]->SetKeyColor(nsGimmick::Door::enDoorColor_Yellow);
		//m_key[4]->SetKeyColor(nsGimmick::Door::enDoorColor_Purple);

		//Vector3 eyeWallPos[3]
		//{
		//	{ -4400.0f, 200.0f,-400.0f },
		//	{-5800.0f, 200.0f, -1000.0f},
		//	{-10400.0f, 200.0f,2000.0f}
		//};

		//Vector3 eyeWalDir[3]
		//{
		//	{ 1.0f,0.0f,0.0f },
		//	{0.0f,0.0f,1.0f},
		//	{ 1.0f,0.0f,0.0f },
		//};
		//	

		//for (int eyeWallNum = 0; eyeWallNum < 3; eyeWallNum++)
		//{
		//	m_eyeWall[eyeWallNum] = NewGO<nsGimmick::EyeWall>(0, "eyeWall");
		//	m_eyeWall[eyeWallNum]->SetPosition(eyeWallPos[eyeWallNum]);
		//	m_eyeWall[eyeWallNum]->SetDirection(eyeWalDir[eyeWallNum]);
		//}

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
		if (m_player->GetPlayerMove()->GetPosition().z <= -4500.0f)
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