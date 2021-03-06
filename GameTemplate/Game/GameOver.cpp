#include "stdafx.h"
#include "GameSceneInclude.h"
#include "TitleScene.h"
namespace nsHikageri
{
	namespace nsGameScene
	{
		using namespace nsGameOverConstant;

		GameOver::~GameOver()
		{
			//DeleteGO(m_gameOverFont);
			DeleteGO(m_gameOverSprite);
		}

		bool GameOver::Start()
		{
			//ゲームオーバー用フォント(仮)
			//m_gameOverFont = NewGO<FontRender>(2);
			//m_gameOverFont->SetText(L"GAME OVER");
			//m_gameOverFont->SetScale(3.0f);
			//m_gameOverFont->SetPosition({ -300.0f, 50.0f });
			//m_gameOverFont->SetColor(m_gameOverFontColor);
			//m_gameOverFont->SetShadowFlag(true);
			//m_gameOverFont->SetShadowOffset(3.0f);
			//m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);

			m_gameOverExecuteCount = INI_GAMEOVER_EXECUTE_COUNT;

			return true;
		}

		void GameOver::Update()
		{
			//カウントが0になったら、終了
			if (m_gameOverExecuteCount <= 0)
			{
				DeleteGO(this);
			}
			else if (m_gameOverExecuteCount == 1)
			{					
				NewGO<nsTitleScene::TitleScene>(0);
			}
			else if (m_gameOverExecuteCount <= DELETE_SPRITE_TIMING)
			{
				//スプライトをじわじわ消す
				if (m_gameOverSpriteColor.a > 0.0f)
				{
					m_gameOverSpriteColor.r -= GAMEOVER_SPRITE_DELETE_SPEED;
					m_gameOverSpriteColor.g -= GAMEOVER_SPRITE_DELETE_SPEED;
					m_gameOverSpriteColor.b -= GAMEOVER_SPRITE_DELETE_SPEED;
					m_gameOverSpriteColor.a -= GAMEOVER_SPRITE_DELETE_SPEED;
					m_gameOverSprite->SetMulColor(m_gameOverSpriteColor);
				}
			}
			else if (m_gameOverExecuteCount == DISPLAY_SPRITE_TIMING)
			{
				DeleteGO(m_gameScene);
				m_gameOverSprite = NewGO<SpriteRender>(7);
				m_gameOverSprite->Init("Assets/Image/Failed.DDS", 1280, 720);
			}
			else if (m_gameOverExecuteCount == INI_GAMEOVER_EXECUTE_COUNT)
			{
				//SE
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/GameOver.wav");
				ss->Play(false);
			}

			if (m_gameOverExecuteCount > 0)
			{
				m_gameOverExecuteCount--;
			}

			//if (m_gameOverExecuteCount > 0)
			//{
			//	m_gameOverExecuteCount--;
			//}

			////カウントが0になったら、終了
			//if (m_gameOverExecuteCount <= 0)
			//{
			//	DeleteGO(this);
			//	DeleteGO(m_gameScene);
			//	NewGO<TitleScene>(0);		
			//}
			////ゲームオーバースプライトが表示され切ったら、、
			//else if (m_gameOverFontColor.a >= MAX_GAMEOVER_SPRITE_ALPHA)
			//{
			//	//Aボタンが押されたら、スプライトを消し始める。
			//	if (g_pad[0]->IsTrigger(enButtonA))
			//	{
			//		m_gameOverExecuteCount = DELETE_SPRITE_TIMING;
			//	}
			//}
			//else if (m_gameOverExecuteCount <= DISPLAY_SPRITE_TIMING)
			//{
			//	//スプライトをじわじわ表示
			//	if (m_gameOverFontColor.a < MAX_GAMEOVER_SPRITE_ALPHA)
			//	{
			//		m_gameOverFontColor.r += ADD_ALPHA_SPEED;	//文字はr値も一緒に加算
			//		m_gameOverFontColor.a += ADD_ALPHA_SPEED;
			//		m_gameOverFont->SetColor(m_gameOverFontColor);
			//		m_gameOverFontShadowColor.a += ADD_ALPHA_SPEED;
			//		m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
			//	}
			//}
		}
	}
}