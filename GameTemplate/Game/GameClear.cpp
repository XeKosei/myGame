#include "stdafx.h"
#include "GameSceneInclude.h"
#include "TitleScene.h"
namespace nsHikageri
{
	namespace nsGameScene
	{
		using namespace nsGameClearConstant;
		GameClear::~GameClear()
		{
		}

		bool GameClear::Start()
		{
			m_whiteSprite = NewGO<SpriteRender>(3);
			m_whiteSprite->Init("Assets/Image/White.DDS", 1280, 720);
			m_whiteSprite->SetMulColor({ 0.0f, 0.0f, 0.0f, 0.0f });

			m_gameClearExecuteCount = INI_GAMECLEAR_EXECUTE_COUNT;
			return true;
		}

		void GameClear::Update()
		{
			//�J�E���g��0�ɂȂ�����A�^�C�g����
			if (m_gameClearExecuteCount <= 0)
			{
				DeleteGO(m_clearFont);
				DeleteGO(this);
				NewGO<nsTitleScene::TitleScene>(0);
			}
			//�N���A���b�Z�[�W�����킶������B
			else if (m_gameClearExecuteCount <= DELETE_CLEARFONT_TIMING)
			{
				if (m_clearFontColor.r > 0.0f)
				{
					m_clearFontColor.r -= CLEARFONT_ADD_SPEED;
					m_clearFontColor.g -= CLEARFONT_ADD_SPEED;
					m_clearFontColor.b -= CLEARFONT_ADD_SPEED;
					m_clearFontColor.a -= CLEARFONT_ADD_SPEED;
					m_clearFont->SetColor(m_clearFontColor);
				}
			}
			//�N���A�t�H���g�����킶��\��
			else if (m_gameClearExecuteCount < DISPLAY_CLEARFONT_TIMING)
			{
				if (m_clearFontColor.r < 1.0f)
				{
					m_clearFontColor.r += CLEARFONT_ADD_SPEED;
					m_clearFontColor.g += CLEARFONT_ADD_SPEED;
					m_clearFontColor.b += CLEARFONT_ADD_SPEED;
					m_clearFontColor.a += CLEARFONT_ADD_SPEED;
					m_clearFont->SetColor(m_clearFontColor);
				}
			}
			//�N���A�t�H���g���쐬
			else if (m_gameClearExecuteCount == DISPLAY_CLEARFONT_TIMING)
			{
				DeleteGO(m_titleNameSprite);
				m_clearFont = NewGO<FontRender>(0);
				m_clearFont->SetText(L"THE ESCAPE is complete.\nThank you for playing.");
				m_clearFont->SetPosition(CLEARFONT_POS);
				m_clearFont->SetColor(m_clearFontColor);
			}
			//�^�C�g���������킶�����
			else if (m_gameClearExecuteCount < DELETE_TITLENAME_TIMING)
			{
				if (m_titleNameColor.r > 0.0f)
				{
					m_titleNameColor.r -= TITLENAME_DELETE_SPEED;
					m_titleNameColor.g -= TITLENAME_DELETE_SPEED;
					m_titleNameColor.b -= TITLENAME_DELETE_SPEED;
					m_titleNameColor.a -= TITLENAME_DELETE_SPEED;
					m_titleNameSprite->SetMulColor(m_titleNameColor);
				}
			}
			//�^�C�g������\��
			else if (m_gameClearExecuteCount == DISPLAY_TITLENAME_TIMING)
			{
				m_titleNameSprite = NewGO<SpriteRender>(0);
				m_titleNameSprite->Init("Assets/Image/Title01.DDS", 1280, 720);
				DeleteGO(m_whiteSprite);
			}
			//���X�v���C�g�����킶��\��
			else if (m_gameClearExecuteCount < INI_GAMECLEAR_EXECUTE_COUNT)
			{
				if (m_whiteSpriteColor.r < 1.0f)
				{
					m_whiteSpriteColor.r += WHITESPRITE_ADD_SPEED;
					m_whiteSpriteColor.g += WHITESPRITE_ADD_SPEED;
					m_whiteSpriteColor.b += WHITESPRITE_ADD_SPEED;
					m_whiteSpriteColor.a += WHITESPRITE_ADD_SPEED;
					m_whiteSprite->SetMulColor(m_whiteSpriteColor);
				}
			}
			//�Q�[���V�[�����폜
			if (m_gameClearExecuteCount == DELETE_GAMESCENE_TIMING)
			{
				DeleteGO(m_gameScene);
				//SE
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/GameClear.wav");
				ss->Play(false);
			}

			//�J�E���g
			if (m_gameClearExecuteCount > 0)
			{
				m_gameClearExecuteCount--;
			}
		}
	}
}