#include "stdafx.h"
#include "GameSceneInclude.h"
#include "BackGroundInclude.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h";
#include "GimmickInclude.h"
#include "ItemInclude.h"
#include "FlashLight.h"
#include "TitleScene.h"

namespace nsHikageri
{
	namespace nsGameScene
	{
		using namespace nsGameSceneConstant;

		GameScene::~GameScene()
		{
			DeleteGO(m_player);
			for (int no = 0; no < ENEMY_NUM; no++)
			{
				DeleteGO(m_enemy[no]);
			}
			DeleteGO(m_backGround);
			DeleteGO(m_secretRoom);
			DeleteGO(m_deadSkeleton);
			DeleteGO(m_flashLight);
			if (m_chandelierManager != nullptr)
				DeleteGO(m_chandelierManager);
			for (int i = 0; i < 6; i++)
			{
				if (m_door[i] != nullptr)
					DeleteGO(m_door[i]);
			}
			for (int i = 0; i < 3; i++)
			{
				if (m_eyeWall[i] != nullptr)
					DeleteGO(m_eyeWall[i]);
			}
			for (int i = 0; i < 5; i++)
			{
				if (m_key[i] != nullptr)
					DeleteGO(m_key[i]);
			}
			if (m_lastKey != nullptr)
				DeleteGO(m_lastKey);
			
			for (int i = 0; i < 3; i++)
			{
				if (m_flashLightParts[i] != nullptr)
					DeleteGO(m_flashLightParts[i]);
			}
			for (int i = 0; i < 10; i++)
			{
				if (m_tranquilizer[i] != nullptr)
					DeleteGO(m_tranquilizer[i]);
			}
			for (int i = 0; i < 15; i++)
			{
				if (m_battery[i] != nullptr)
					DeleteGO(m_battery[i]);
			}
			for (int no = 0; no < 5; no++)
			{
				DeleteGO(m_messagePaper[no]);
			}
			if (m_pointLight != nullptr)
				DeleteGO(m_pointLight);

			DeleteGO(m_dirLig);
		}

		bool GameScene::Start()
		{
			//ディレクションライトを作成
			m_dirLig = NewGO<DirectionLight>(0);
			m_dirLig->SetDirection({ 0.0f, 0.0f, -1.0f });
			m_dirLig->SetColor({ 0.8f,0.8f,0.8f });

			//プレイヤーを作成
			m_player = NewGO<nsPlayer::Player>(0);
			//懐中電灯を生成
			m_flashLight = NewGO<nsFlashLight::FlashLight>(0);
			m_player->SetFlashLight(m_flashLight);		
			m_flashLight->SetPlayer(m_player);
			
			//エネミーを作成
			for (int no = 0; no < ENEMY_NUM; no++)
			{
				m_enemy[no] = NewGO<nsEnemy::Enemy>(0, "enemy");
				m_enemy[no]->SetPlayer(m_player);
			}
			m_enemy[1]->SetIniSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_None);
			m_enemy[2]->SetIniSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_None);

			//ステージを作成
			m_backGround = NewGO<nsBackGround::BackGround>(0, "backGround");
			m_secretRoom = NewGO<nsBackGround::SecretRoom>(0, "secretRoom");
			m_secretRoom->Init(m_player);
			m_deadSkeleton = NewGO<nsBackGround::DeadSkeleton>(0, "deadSkeleton");

			//シャンデリア
			m_chandelierManager = NewGO<nsGimmick::ChandelierManager>(0);
			m_chandelierManager->SetPlayer(m_player);
			m_chandelierManager->SetEnemy(m_enemy[0]);
			
			//ドア　テスト
			Vector3 doorPos[6]
			{
				{ 0.0f, 0.0f, -100.0f },
				{-900.0f, 0.0f, -600.0f},
				{-800.0f, 0.0f, -1900.0f},
				{-7200.0f,0.0f, 1500.0f},
				{-7900.0f, 0.0f, 5400.0f},
				{2300.0f, 0.0f, 6200.0f}
			};

			Vector3 doorDir[6]
			{
				{1.0f,0.0f,0.0f },
				{0.0f, 0.0f, 1.0f},
				{-1.0f, 0.0f, 0.0f},
				{1.0f,0.0f,0.0f},
				{0.0f,0.0f,-1.0f},
				{0.0f, 0.0f, 1.0f}
			};

			for (int doorNum = 0; doorNum < 6; doorNum++)
			{
				m_door[doorNum] = NewGO<nsGimmick::Door>(0);
				m_door[doorNum]->SetPlayer(m_player);
				//m_door[doorNum]->SetEnemy(m_enemy);
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
				{1500.0f, 145.0f, 50.0f},
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

			//最後の鍵
			m_lastKey = NewGO<nsItem::ItemKey>(0);
			m_lastKey->SetPlayer(m_flashLight->GetPlayer());
			m_lastKey->SetKeyColor(nsGimmick::Door::enDoorColor_White);
			Vector3 lastKeyPos = { 20000.0f, 0.0f, 20000.0f };
			m_lastKey->SetPosition(lastKeyPos);

			//懐中電灯のパーツテスト
			Vector3 partsPos[3] = {
				{700.0f, 145.0f, -2000.0f},
				{ -7900.0f, 145.0f, 1600.0f },
				{2200.0f, 145.0f, 10520.0f},
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
				{-4300.0, 145.0f, 4900.0f},
				{-2700.0f, 145.0f, 7300.0f},
				{2700.0f, 145.0f, 6500.0f}
			};

			for (int no = 0; no < 10; no++)
			{
				m_tranquilizer[no] = NewGO<nsItem::ItemTranquilizer>(0);
				m_tranquilizer[no]->SetPlayer(m_player);
				m_tranquilizer[no]->SetPosition(tranquilizerPos[no]);
			}
			
			//電池
			Vector3 batteryPos[13] = {
				{-600.0f,145.0f, 700.0f},	
				{-1200.0f, 145.0f,3500.0f },
				{-300.0f, 145.0f,-1500.0f },
				{-6100.0f, 145.0f,4870.0f },
				{-5700.0f, 145.0f, 4500.0f},
				{-9500.0f, 145.0f, 5800.0f},
				{-8500.0f, 145.0f, 5600.0f},
				{-5710.0f, 145.0f, -1700.0f},
				{-5610.0f, 145.0f, -1700.0f},
				{-7040.0f, 145.0f, -2900.0f},
				{-6000, 145.0f, 7400.0f},
				{-1500.0f, 145.0f, 9200.0f},
				{2600.0f, 145.0f, 10200.0f}
			};
			
			for (int no = 0; no < 13; no++)
			{
				m_battery[no] = NewGO<nsItem::ItemBattery>(0);
				m_battery[no]->SetPlayer(m_player);
				m_battery[no]->SetPosition(batteryPos[no]);
			}
			
			//メッセージペーパー
			Vector3 messagePaperPos[6] = {
				{1500.0f, 145.0f, -100.0f},
				{-1700.0f, 145.0f, -3300.0f},
				{-200.0f, 145.0f,-1500.0f },
				{-7900.0f, 145.0f,1700.0f },
				{1800.0f, 145.0f, 10200.0f},
				{3900.0f, 5.0f, 5250.0f},
			};

			for (int no = 0; no < 6; no++)
			{
				m_messagePaper[no] = NewGO<nsItem::ItemMessagePaper>(0);
				m_messagePaper[no]->SetPlayer(m_player);
				m_messagePaper[no]->SetPosition(messagePaperPos[no]);
			}
			m_messagePaper[0]->SetMessagePaperText(nsItem::ItemMessagePaper::enMessagePaperKind_00);
			m_messagePaper[1]->SetMessagePaperText(nsItem::ItemMessagePaper::enMessagePaperKind_01);
			m_messagePaper[2]->SetMessagePaperText(nsItem::ItemMessagePaper::enMessagePaperKind_02);
			m_messagePaper[3]->SetMessagePaperText(nsItem::ItemMessagePaper::enMessagePaperKind_03);
			m_messagePaper[4]->SetMessagePaperText(nsItem::ItemMessagePaper::enMessagePaperKind_04);
			m_messagePaper[5]->SetMessagePaperText(nsItem::ItemMessagePaper::enMessagePaperKind_05);

			//出口の明かり
			m_pointLight = NewGO<PointLight>(0);
			m_pointLight->SetColor({500.0f,500.0f,500.0f});
			m_pointLight->SetRange(2000.0f);
			m_pointLight->SetPosition({11000.0f,0.0f, 5200.0f});

			return true;
		}

		void GameScene::Update()
		{
			if (m_chaseBGMCanPlayFlag)
			{
				if (m_enemy[0]->GetEnemyState() == nsEnemy::Enemy::enState_Chase ||
					m_enemy[0]->GetEnemyState() == nsEnemy::Enemy::enState_Scream
					)
				{
					m_chaseBGMCanPlayFlag = false;

					m_chaseBGM = NewGO<SoundSource>(0);
					m_chaseBGM->Init(L"Assets/sound/ChaseBGM.wav");
					m_chaseBGM->SetVolume(2.0f);
					m_chaseBGM->Play(true);
				}
			}
			else
			{
				if (m_enemy[0]->GetEnemyState() == nsEnemy::Enemy::enState_SearchPlayer ||
					m_enemy[0]->GetEnemyState() == nsEnemy::Enemy::enState_Petrifaction)
				{
					DeleteGO(m_chaseBGM);
					m_chaseBGM = nullptr;
					m_chaseBGMCanPlayFlag = true;
				}
			}

			m_dirLig->SetDirection(g_camera3D->GetForward());

			switch (m_gameStep)
			{
			case enGameStep_01:
				GameManagement();
				ExecuteUpdateStep01();
				break;
			case enGameStep_02:
				GameManagement();
				ExecuteUpdateStep02();
				break;
			case enGameStep_03:
				GameManagement();
				ExecuteUpdateStep03();
				break;
			case enGameStep_04:
				GameManagement();
				ExecuteUpdateStep04();
				break;
			case enGameStep_05:
				GameManagement();
				ExecuteUpdateStep05();
				break;
			case enGameStep_06:
				GameManagement();
				ExecuteUpdateStep06();
				break;
			case enGameStep_07:
				GameManagement();
				ExecuteUpdateStep07();
				break;
			case enGameStep_08:
				GameManagement();
				ExecuteUpdateStep08();
				break;
			case enGameStep_09:
				GameManagement();
				ExecuteUpdateStep09();
				break;
			case enGameStep_num:
				GameManagement();
			default:
				break;
			}
		}

		void GameScene::GameManagement()
		{
			if (m_player->GetPlayerSanity()->GetSanityValue() <= 0.0f)
			{
				m_gameStep = enGameStep_GameOver;
				m_gameOver = NewGO<GameOver>(0);
				m_gameOver->SetGameScene(this);
			}
			if (m_player->GetPlayerMove()->GetPosition().x >= 11400.0f)
			{
				m_gameStep = enGameStep_GameClear;
				m_gameClear = NewGO<GameClear>(0);
				m_gameClear->SetGameScene(this);
			}
			//最後の通路はプレイヤーのSAN値を減らさない。
			if (m_player->GetPlayerMove()->GetPosition().x >= 2500.0f)
			{
				m_player->GetPlayerSanity()->SetReliefFlag(true);
			}
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
				//エネミー一体目の配置位置を変更
				m_enemy[0]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_2);
				m_enemy[0]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[0]->GetEnemySearchPlayer()->CalcNextSearchPos();			
				//エネミー二体目を配置
				m_enemy[1]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_3);
				m_enemy[1]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[1]->GetEnemySearchPlayer()->CalcNextSearchPos();

				m_gameStep = enGameStep_04;
			}
		}
		void GameScene::ExecuteUpdateStep04()
		{
			if (m_door[4]->GetUnlockFlag())
			{
				//エネミー一体目の配置位置を変更
				m_enemy[0]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_4);
				m_enemy[0]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[0]->GetEnemySearchPlayer()->CalcNextSearchPos();
				//エネミー二体目の配置位置を変更
				m_enemy[1]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_5);
				m_enemy[1]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[1]->GetEnemySearchPlayer()->CalcNextSearchPos();
				//エネミー三体目を配置
				m_enemy[2]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_6);
				m_enemy[2]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[2]->GetEnemySearchPlayer()->CalcNextSearchPos();

				m_gameStep = enGameStep_05;
			}
		}
		void GameScene::ExecuteUpdateStep05()
		{
			if (m_player->GetFlashLight()->GetAbilityMedousaEye()->GetAbilityActiveFlag())
			{
				//エネミー二体目をいなくする
				m_enemy[1]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_None);
				m_enemy[1]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[1]->GetEnemySearchPlayer()->CalcNextSearchPos();
				//エネミー三体目をいなくする
				m_enemy[2]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_None);
				m_enemy[2]->SetEnemyState(nsEnemy::Enemy::enState_SearchPlayer);
				m_enemy[2]->GetEnemySearchPlayer()->CalcNextSearchPos();

				m_gameStep = enGameStep_06;
			}
		}
		void GameScene::ExecuteUpdateStep06()
		{	
			if (m_enemy[0]->GetEnemyState() == nsEnemy::Enemy::enState_Petrifaction)
			{
				//鍵を落とす
				m_lastKey->SetPosition(m_enemy[0]->GetEnemyMove()->GetPosition());

				m_gameStep = enGameStep_07;
			}
		}

		void GameScene::ExecuteUpdateStep07()
		{
			Vector3 plPos = m_player->GetPlayerMove()->GetPosition();
			if (plPos.x >= 3000.0f)
			{
				m_flashLight->SetIsBreak(true);
				m_gameStep = enGameStep_08;
			}
		}
		void GameScene::ExecuteUpdateStep08()
		{
			Vector3 plPos = m_player->GetPlayerMove()->GetPosition();
			if (plPos.x >= 6500.0f)
			{
				//エネミー二体目を配置
				m_enemy[1]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_Last1);
				m_enemy[1]->SetEnemyState(nsEnemy::Enemy::enState_Chase);
				//エネミー三体目を配置
				m_enemy[2]->GetEnemySearchPlayer()->SetSearchPos(nsEnemy::EnemySearchPlayer::enSearchArea_Last2);
				m_enemy[2]->SetEnemyState(nsEnemy::Enemy::enState_Chase);

				m_gameStep = enGameStep_09;
			}
		}
		void GameScene::ExecuteUpdateStep09()
		{


		}
	}
}