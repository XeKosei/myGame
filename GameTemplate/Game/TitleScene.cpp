#include "stdafx.h"
#include "TitleScene.h"
#include "TitleSceneConstant.h"
#include "GameScene.h"

namespace nsHikageri
{
	namespace nsTitleScene
	{
		using namespace nsTitleSceneConstant;

		TitleScene::~TitleScene()
		{
			DeleteGO(m_titleSprite);
			DeleteGO(m_titleFont);
			DeleteGO(m_synopsisFont);
			DeleteGO(m_blackSprite);
		}

		bool TitleScene::Start()
		{
			m_titleSprite = NewGO<SpriteRender>(0);
			m_titleSprite->Init("Assets/Image/Title01.DDS", 1280, 720);
			m_titleSprite->SetMulColor({ 0.0f,0.0f,0.0f,0.0f });

			m_titleFont = NewGO<FontRender>(0);
			m_titleFont->SetText(L"PressA : GameStart");
			m_titleFont->SetPosition(TITLEFONT_POS);
			m_titleFont->SetColor(m_titleFontColor);
			m_titleFont->SetScale(TITLEFONT_SCALE);

			m_synopsisFont = NewGO<FontRender>(7);
			m_synopsisFont->SetText(SYNOPSIS);
			m_synopsisFont->SetPosition(SYNOPSISFONT_POS);
			m_synopsisFont->SetColor(m_synopsisFontColor);
			m_synopsisFont->SetScale(SYNOPSISFONT_SCALE);
			
			m_firstMoveFlag = true;
			
			//曲を再生
			m_titleBGM = NewGO<SoundSource>(0);
			m_titleBGM->Init(L"Assets/sound/TitleBGM.wav");
			m_titleBGM->Play(true);

			//タイトル表示SE
			SoundSource* titleDispSS = NewGO<SoundSource>(0);
			titleDispSS->Init(L"Assets/sound/TitleDisp.wav");
			titleDispSS->Play(false);

			return true;
		}

		void TitleScene::Update()
		{
			FirstMove();
			SecondMove();
			Blinking();
			DeleteMove();
			Synopsis();
			GameStart();
		}

		void TitleScene::FirstMove()
		{
			//タイトル画面の表示
			if (m_firstMoveFlag)
			{
				m_titleSpriteColor.r += TITLESPRITE_COLOR_ADD_SPEED;
				m_titleSpriteColor.g += TITLESPRITE_COLOR_ADD_SPEED;
				m_titleSpriteColor.b += TITLESPRITE_COLOR_ADD_SPEED;
				m_titleSpriteColor.a += TITLESPRITE_COLOR_ADD_SPEED;

				m_titleSprite->SetMulColor(m_titleSpriteColor);

				if (m_titleSpriteColor.r >= 1.0f)
				{
					m_titleSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
					m_titleSprite->SetMulColor(m_titleSpriteColor);
					m_firstMoveFlag = false;
					m_secondMoveFlag = true;
					m_secondMoveInterval = SECOND_MOVE_INTERVAL;
				}
			}
		}

		void TitleScene::SecondMove()
		{
			//タイトル画面のフォントの表示
			if (m_secondMoveFlag)
			{
				if (m_secondMoveInterval > 0)
				{
					m_secondMoveInterval--;
					return;
				}

				m_titleFontColor.r += TITLEFONT_COLOR_ADD_SPEED;
				m_titleFontColor.g += TITLEFONT_COLOR_ADD_SPEED;
				m_titleFontColor.b += TITLEFONT_COLOR_ADD_SPEED;
				m_titleFontColor.a += TITLEFONT_COLOR_ADD_SPEED;

				m_titleFont->SetColor(m_titleFontColor);

				if (m_titleFontColor.r >= 1.0f)
				{
					m_titleFontColor = { 1.0f,1.0f,1.0f,1.0f };
					m_titleFont->SetColor(m_titleFontColor);
					m_secondMoveFlag = false;
					m_blinkingFlag = true;
				}
			}
		}

		void TitleScene::Blinking()
		{
			//点滅
			if (m_blinkingFlag)
			{
				if (m_blinkingAddColorFlag)
				{
					m_titleFontColor.r += BLINKING_COLOR_ADD_SPEED;
					m_titleFontColor.g += BLINKING_COLOR_ADD_SPEED;
					m_titleFontColor.b += BLINKING_COLOR_ADD_SPEED;
					m_titleFontColor.a += BLINKING_COLOR_ADD_SPEED;

					if (m_titleFontColor.r >= 1.0f)
					{
						m_blinkingAddColorFlag = false;
					}
				}
				else
				{
					m_titleFontColor.r -= BLINKING_COLOR_ADD_SPEED;
					m_titleFontColor.g -= BLINKING_COLOR_ADD_SPEED;
					m_titleFontColor.b -= BLINKING_COLOR_ADD_SPEED;
					m_titleFontColor.a -= BLINKING_COLOR_ADD_SPEED;

					if (m_titleFontColor.r <= BLINKING_MIN_COLOR)
					{
						m_blinkingAddColorFlag = true;
					}
				}

				m_titleFont->SetColor(m_titleFontColor);
			}
		}

		void TitleScene::DeleteMove()
		{
			if (m_blinkingFlag == true && m_deleteMoveFlag == false)
			{
				//タイトル画面を消す
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//曲を消す
					DeleteGO(m_titleBGM);

					m_firstMoveFlag = false;
					m_secondMoveFlag = false;
					m_blinkingFlag = false;
					m_deleteMoveFlag = true;
					m_titleSpriteColor = { TITLESPRITE_DELETE_MAX_COLOR,TITLESPRITE_DELETE_MAX_COLOR,TITLESPRITE_DELETE_MAX_COLOR,TITLESPRITE_DELETE_MAX_COLOR };
					m_titleFont->SetColor({ 0.0f,0.0f,0.0f,0.0f });

					//SE
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/TitleGameStart.wav");
					ss->Play(false);
				}
			}
			if (m_deleteMoveFlag)
			{
				m_titleSpriteColor.r -= TITLESPRITE_DELETE_SPEED;
				m_titleSpriteColor.g -= TITLESPRITE_DELETE_SPEED;
				m_titleSpriteColor.b -= TITLESPRITE_DELETE_SPEED;
				m_titleSpriteColor.a -= TITLESPRITE_DELETE_SPEED;

				m_titleSprite->SetMulColor(m_titleSpriteColor);

				if (m_titleSpriteColor.r <= 0.0f)
				{
					m_titleSpriteColor = {0.0f,0.0f,0.0f,0.0f};
					m_titleSprite->SetMulColor(m_titleSpriteColor);
					m_deleteMoveFlag = false;
					m_synopsisFlag = true;	
					
					//黒背景の表示
					m_blackSprite = NewGO<SpriteRender>(6);
					m_blackSprite->Init("Assets/image/Black.DDS", 1280, 720);
				}
			}
		}

		void TitleScene::Synopsis()
		{
			//あらすじの表示
			if (m_synopsisFlag)
			{
				m_synopsisFontColor.r += SYNOPSISFONT_COLOR_ADD_SPEED;
				m_synopsisFontColor.g += SYNOPSISFONT_COLOR_ADD_SPEED;
				m_synopsisFontColor.b += SYNOPSISFONT_COLOR_ADD_SPEED;
				m_synopsisFontColor.a += SYNOPSISFONT_COLOR_ADD_SPEED;

				m_synopsisFont->SetColor(m_synopsisFontColor);

				if (m_synopsisFontColor.r >= 1.0f)
				{
					m_synopsisFontColor = { 1.0f,1.0f,1.0f,1.0f };
					m_synopsisFont->SetColor(m_synopsisFontColor);
					nsGameScene::GameScene* gameScene = NewGO<nsGameScene::GameScene>(0, "gameScene");
					m_synopsisFlag = false;
					m_synopsisDeleteFlag = true;
				}
			}

			if (m_synopsisDeleteFlag)
			{
				m_synopsisFontColor.r -= SYNOPSISFONT_COLOR_ADD_SPEED;
				m_synopsisFontColor.g -= SYNOPSISFONT_COLOR_ADD_SPEED;
				m_synopsisFontColor.b -= SYNOPSISFONT_COLOR_ADD_SPEED;
				m_synopsisFontColor.a -= SYNOPSISFONT_COLOR_ADD_SPEED;

				m_synopsisFont->SetColor(m_synopsisFontColor);

				if (m_synopsisFontColor.r <= 0.0f)
				{
					m_synopsisFontColor = {0.0f,0.0f,0.0f,0.0f};
					m_synopsisFont->SetColor(m_synopsisFontColor);
					m_gameStartMoveFlag = true;
				}
			}
		}

		void TitleScene::GameStart()
		{
			//黒背景を消す
			if (m_gameStartMoveFlag)
			{
				m_blackSpriteColor.r -= BLACKSPRITE_DELETE_SPEED;
				m_blackSpriteColor.g -= BLACKSPRITE_DELETE_SPEED;
				m_blackSpriteColor.b -= BLACKSPRITE_DELETE_SPEED;
				m_blackSpriteColor.a -= BLACKSPRITE_DELETE_SPEED;

				m_blackSprite->SetMulColor(m_blackSpriteColor);

				if (m_blackSpriteColor.r <= 0.0f)
				{
					DeleteGO(this);
				}
			}
		}
	}
}