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

		//シャンデリア　テスト
		Vector3 chandelierPos[10] = {
			{ 1000.0f,800.0f,0.0f } ,
			{ -1000.0f, 800.0f, 1000.0f},
			{-1400.0f, 800.0f, -3600.0f},
			{-1000.0f, 800.0f, 3400.0f},
			{0.0f, 800.0f, -2000.0f},
			{-4600.0f, 800.0f, 2800.0f},
			{-9000.0f, 800.0f,6000.0f},
			{-4600.0f, 800.0f, 4400.0f},
			{600.0f, 800.0f, 4400.0f,},
			{600.0f, 800.0f, 6000.0f,}
		};

		for (int chandelierNum = 0; chandelierNum < 10; chandelierNum++)
		{
			m_chandelier[chandelierNum] = NewGO<nsGimmick::Chandelier>(1);
			m_chandelier[chandelierNum]->SetPlayer(m_player);
			m_chandelier[chandelierNum]->SetEnemy(m_enemy);
			m_chandelier[chandelierNum]->SetPosition(chandelierPos[chandelierNum]);
		}

		//ドア　テスト
		Vector3 doorPos[6]
		{
			{ 0.0f, 0.0f, -100.0f },
			{-900.0f, 0.0f, -600.0f},
			{-800.0f, 0.0f, -1900.0f},
			{-7200.0f,0.0f, 1500.0f},
			{-7900.0f, 0.0f, 5400.0f},
			{1600.0f, 0.0f, 6900.0f}
		};

		Vector3 doorDir[6]
		{
			{1.0f,0.0f,0.0f },
			{0.0f, 0.0f, 1.0f},
			{-1.0f, 0.0f, 0.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,0.0f,-1.0f},
			{-1.0f, 0.0f, 0.0f}
		};

		for (int doorNum = 0; doorNum < 6; doorNum++)
		{
			m_door[doorNum] = NewGO<nsGimmick::Door>(0);
			m_door[doorNum]->SetPlayer(m_player);
			m_door[doorNum]->SetEnemy(m_enemy);
			m_door[doorNum]->SetPosition(doorPos[doorNum]);
			m_door[doorNum]->SetDirection(doorDir[doorNum]);
		}
		m_door[0]->SetDoorColor(nsGimmick::Door::enDoorColor_Red);
		m_door[1]->SetDoorColor(nsGimmick::Door::enDoorColor_Blue);
		m_door[2]->SetDoorColor(nsGimmick::Door::enDoorColor_Green);
		m_door[3]->SetDoorColor(nsGimmick::Door::enDoorColor_Yellow);
		m_door[4]->SetDoorColor(nsGimmick::Door::enDoorColor_Purple);
		m_door[5]->SetDoorColor(nsGimmick::Door::enDoorColor_White);

		//鍵テスト
		Vector3 keyPos[5] = {
			{1500.0f, 145.0f, 0.0f},
			{ -2290.0f, 145.0f, 400.0f },
			{110.0f, 145.0f, 2800.0f},
			{-10800.0f,145.0f, 2200.0f},
			{-7000.0f, 145.0f, -1900.0f}
		};

		for (int keyNum = 0; keyNum < 5; keyNum++)
		{
			m_key[keyNum] = NewGO<nsItem::ItemKey>(0);
			m_key[keyNum]->SetPlayer(m_player);
			m_key[keyNum]->SetPosition(keyPos[keyNum]);
		}
		m_key[0]->SetKeyColor(nsGimmick::Door::enDoorColor_Red);
		m_key[1]->SetKeyColor(nsGimmick::Door::enDoorColor_Blue);
		m_key[2]->SetKeyColor(nsGimmick::Door::enDoorColor_Green);
		m_key[3]->SetKeyColor(nsGimmick::Door::enDoorColor_Yellow);
		m_key[4]->SetKeyColor(nsGimmick::Door::enDoorColor_Purple);

		//懐中電灯のパーツテスト
		Vector3 partsPos[3] = {
			{700.0f, 145.0f, -2000.0f},
			{ -7900.0f, 145.0f, 1600.0f },
			{600.0f, 145.0f, 3480.0f},
		};

		for (int partsNum = 0; partsNum < 3; partsNum++)
		{
			m_flashLightParts[partsNum] = NewGO<nsItem::ItemFlashLightParts>(0);
			m_flashLightParts[partsNum]->SetPlayer(m_player);
			m_flashLightParts[partsNum]->SetPosition(partsPos[partsNum]);
		}
		m_flashLightParts[0]->SetPartsType(nsItem::ItemFlashLightParts::enFlashLightPartsTypes_StrobeFlash);
		m_flashLightParts[1]->SetPartsType(nsItem::ItemFlashLightParts::enFlashLightPartsTypes_Clairvoyance);
		m_flashLightParts[2]->SetPartsType(nsItem::ItemFlashLightParts::enFlashLightPartsTypes_MedousaEye);

		Vector3 eyeWallPos[3] = 
		{
			{ -4400.0f, 200.0f,-400.0f },
			{-5800.0f, 200.0f, -1000.0f},
			{-10400.0f, 200.0f,2000.0f}
		};

		Vector3 eyeWalDir[3] = 
		{
			{ 1.0f,0.0f,0.0f },
			{0.0f,0.0f,1.0f},
			{ 1.0f,0.0f,0.0f },
		};
			

		for (int eyeWallNum = 0; eyeWallNum < 3; eyeWallNum++)
		{
			m_eyeWall[eyeWallNum] = NewGO<nsGimmick::EyeWall>(0, "eyeWall");
			m_eyeWall[eyeWallNum]->SetPosition(eyeWallPos[eyeWallNum]);
			m_eyeWall[eyeWallNum]->SetDirection(eyeWalDir[eyeWallNum]);
		}
		
		//精神安定剤
		Vector3 tranquilizerPos[10] = {
			{-1200.0f, 145.0f, -3500.0f},
			{-2900.0f, 145.0f, 3600.0f},
			{-1300.0f,145.0f, 3500.0f},
			{-5000.0f, 145.0f, -1300.0f},
			{-4700.0f, 145.0f,3000.0f},
			{-6300.0f, 145.0f,4870.0f },
			{-5930.0f, 145.0f, -1780.0f},
			{-4300.0, 145.0f, 4500.0f},
			{1110.0f, 145.0f, 7600.0f},
			{1040.0f, 145.0f, 5400.0f},
		};

		for (int no = 0; no < 10; no++)
		{
			m_tranquilizer[no] = NewGO<nsItem::ItemTranquilizer>(0);
			m_tranquilizer[no]->SetPlayer(m_player);
			m_tranquilizer[no]->SetPosition(tranquilizerPos[no]);
		}

		//電池
		Vector3 batteryPos[15] = {
			{-600.0f,145.0f, 700.0f},
			{-1700.0f, 145.0f, -3500.0f},
			{-1200.0f, 145.0f,3500.0f },
			{-300.0f, 145.0f,-1500.0f },
			{-200.0f, 145.0f, -1500.0f},
			{-6100.0f, 145.0f,4870.0f },
			{-5700.0f, 145.0f, 4500.0f},
			{-9500.0f, 145.0f, 5800.0f},
			{-8500.0f, 145.0f, 5600.0f},
			{-5710.0f, 145.0f, -1700.0f},
			{-5610.0f, 145.0f, -1700.0f},
			{-7040.0f, 145.0f, -2900.0f},
			{-4900.0f, 145.0f, 4600.0f},
			{160.0f, 145.0f, 6200.0f},
			{60.0f, 145.0f, 3800.0f}
		};

		for (int no = 0; no < 15; no++)
		{
			m_battery[no] = NewGO<nsItem::ItemBattery>(0);
			m_battery[no]->SetPlayer(m_player);
			m_battery[no]->SetPosition(batteryPos[no]);
		}

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
		switch (m_gameStep)
		{
		case enGameStep_01:
			ExecuteUpdateStep01();
			break;
		case enGameStep_02:
			ExecuteUpdateStep02();
			break;
		case enGameStep_03:
			ExecuteUpdateStep03();
			break;
		case enGameStep_04:
			ExecuteUpdateStep04();
			break;
		case enGameStep_05:
			ExecuteUpdateStep05();
			break;
		default:
			break;
		}

		GameClear();
	}

	void GameScene::ExecuteUpdateStep01()
	{
		if (m_door[0]->GetUnlockFlag())
		{
			m_gameStep = enGameStep_02;
		}
	}
	void GameScene::ExecuteUpdateStep02()
	{
		if (m_door[1]->GetUnlockFlag())
		{
			m_gameStep = enGameStep_03;
		}
	}
	void GameScene::ExecuteUpdateStep03()
	{
		if (m_eyeWall[0]->GetDisapperFlag())
		{
			m_enemy->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_2);
			m_enemy->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
			m_enemy->GetEnemySearchPlayer()->CalcNextSearchPos();
			m_gameStep = enGameStep_04;
		}
	}
	void GameScene::ExecuteUpdateStep04()
	{
		if (m_door[4]->GetUnlockFlag())
		{
			m_enemy->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_3);
			m_enemy->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
			m_enemy->GetEnemySearchPlayer()->CalcNextSearchPos();
			m_gameStep = enGameStep_05;
		}
	}
	void GameScene::ExecuteUpdateStep05()
	{

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